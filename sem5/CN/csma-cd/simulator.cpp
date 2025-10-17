#include "simulator.h"
#include <random>
#include <iostream>

static int ceil_div_int(int a, int b) { return (a + b - 1) / b; }

Simulator::Simulator(std::shared_ptr<Channel> ch,
                     std::map<std::string, Station> &st,
                     double time_seconds_cap,
                     double collision_probability,
                     std::mt19937 &random_engine)
    : channel(std::move(ch)),
      stations(st),
      simulation_time_cap(time_seconds_cap),
      collision_prob(collision_probability),
      rng(random_engine),
      total_success_bytes(0),
      total_success_frames(0),
      total_forwarding_delay_slots(0),
      time_elapsed_slots(0),
      collision_events(0),
      ongoing_frame_bytes(0)
{
    log_file.open("log.txt", std::ios::out | std::ios::trunc);
}

Simulator::~Simulator()
{
    if (log_file.is_open())
        log_file.close();
}

bool Simulator::all_done() const
{
    if (channel->busy)
        return false;
    if (!channel->current_station_id.empty())
        return false;
    for (std::map<std::string, Station>::const_iterator it = stations.begin(); it != stations.end(); ++it)
    {
        if (it->second.frames_remaining() > 0)
            return false;
        if (it->second.is_sending)
            return false;
    }
    return true;
}

void Simulator::run()
{
    int slots_cap = static_cast<int>(simulation_time_cap * 1000.0);
    if (slots_cap < 1)
        slots_cap = 1;

    std::uniform_real_distribution<double> uni01(0.0, 1.0);

    int now = 0;
    for (std::map<std::string, Station>::iterator it = stations.begin(); it != stations.end(); ++it)
    {
        if (it->second.frames_remaining() > 0)
            it->second.current_frame_start_slot = now;
    }

    while (slots_cap > 0)
    {
        if (all_done())
        {
            std::cout << "All stations finished sending their frames. Stopping early.\n";
            break;
        }

        bool is_jamming_active = false;
        for (std::map<std::string, Station>::iterator it = stations.begin(); it != stations.end(); ++it)
        {
            if (it->second.jamming)
            {
                is_jamming_active = true;
                std::cout << "Jamming signal sent by Station " << it->second.id << "\n";
                it->second.jamming = false;
                break;
            }
        }
        if (is_jamming_active)
        {
            ++now;
            --slots_cap;
            ++time_elapsed_slots;
            continue;
        }

        if (!channel->busy)
        {
            if (channel->busy_delay > 0)
                --channel->busy_delay;
            if (channel->finish_delay > 0)
                --channel->finish_delay;

            if (channel->busy_delay == 0 && !channel->current_station_id.empty())
            {
                channel->busy = true;
                std::cout << "Channel is now BUSY.\n";
            }

            std::vector<Station *> ready_stations;
            ready_stations.reserve(stations.size());
            for (std::map<std::string, Station>::iterator it = stations.begin(); it != stations.end(); ++it)
            {
                if (it->second.should_transmit())
                    ready_stations.push_back(&it->second);
            }

            if (channel->current_station_id.empty() && ready_stations.size() == 1)
            {
                Station *station = ready_stations[0];
                double r = uni01(rng);
                if (r < collision_prob)
                {
                    ++collision_events;
                    std::cout << "Random collision/noise hit Station " << station->id << " during acquisition; backoff.\n";
                    std::cout << "[COLLISION] Station " << station->id
                              << " collided. ";

                    bool dropped = station->exponential_backoff();
                    std::cout << "[BACKOFF] " << station->id
                              << " -> k=" << station->k
                              << ", wait=" << station->waiting_period << " slots";
                    if (dropped)
                    {
                        std::cout << " (DROPPED frame)";
                        station->advance_after_drop(now);
                    }
                    std::cout << "\n";
                }
                else
                {
                    ongoing_frame_bytes = station->hol_frame_bytes();
                    int tx_time = ceil_div_int(ongoing_frame_bytes, channel->bandwidth);
                    if (tx_time <= 0)
                        tx_time = 1;
                    channel->busy_delay = channel->Tp;
                    channel->finish_delay = tx_time;
                    channel->current_station_id = station->id;
                    station->is_sending = true;
                    std::cout << "Station " << station->id << " started sending.\n";
                }
            }
            else if (!ready_stations.empty())
            {
                ++collision_events;

                if (!channel->current_station_id.empty())
                {
                    std::cout << "Station " << channel->current_station_id << " was interrupted. ";
                    std::cout << "[INTERRUPT] In-flight sender " << channel->current_station_id
                              << " interrupted by collision.\n";
                    stations.at(channel->current_station_id).interrupt();
                }

                std::cout << "Collision! Stations performing backoff: ";
                std::cout << "[COLLISION] Stations ";
                for (std::size_t i = 0; i < ready_stations.size(); ++i)
                {
                    log_file << ready_stations[i]->id << " ";
                    std::cout << ready_stations[i]->id << (i + 1 < ready_stations.size() ? ", " : "");
                }
                log_file << "\n";
                std::cout << "\n";

                for (std::size_t i = 0; i < ready_stations.size(); ++i)
                {
                    Station *s = ready_stations[i];
                    bool dropped = s->exponential_backoff();
                    std::cout << "[BACKOFF] " << s->id
                              << " -> k=" << s->k
                              << ", wait=" << s->waiting_period << " slots";
                    if (dropped)
                    {
                        std::cout << " (DROPPED frame)";
                        s->advance_after_drop(now);
                    }
                    std::cout << "\n";
                }
            }
            else
            {
                std::cout << "Channel is idle.\n";
            }
        }
        else
        {
            if (channel->finish_delay > 0)
                --channel->finish_delay;

            if (channel->finish_delay == 0)
            {
                Station &st = stations.at(channel->current_station_id);

                ++st.successful_transmissions;
                st.is_sending = false;

                int delay_slots = now - st.current_frame_start_slot;
                if (delay_slots < 0)
                    delay_slots = 0;
                total_forwarding_delay_slots += static_cast<long long>(delay_slots);
                total_success_frames += 1;
                total_success_bytes += static_cast<long long>(ongoing_frame_bytes);
                ongoing_frame_bytes = 0;

                st.drop_period = 1;
                std::cout << "Transmission from " << st.id << " successful. Channel is now FREE.\n";

                channel->current_station_id.clear();
                channel->busy = false;

                st.advance_after_success(now);
            }
            else
            {
                std::cout << "Channel is busy with transmission from "
                          << channel->current_station_id << ".\n";
            }
        }

        ++now;
        --slots_cap;
        ++time_elapsed_slots;
    }

    if (!all_done())
    {
        std::cout << "Simulation ended due to time cap.\n";
    }
}
