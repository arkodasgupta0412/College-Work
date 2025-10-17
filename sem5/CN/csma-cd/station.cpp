#include "station.h"
#include <random>

Station::Station(std::string station_id,
                 double p,
                 int kmax,
                 const std::vector<int> &frames_bytes,
                 std::shared_ptr<Channel> ch,
                 std::mt19937 &random_generator)
    : channel(ch),
      p_persistence(p),
      rng(random_generator),
      id(std::move(station_id)),
      max_backoff_attempts(kmax),
      waiting_period(0),
      drop_period(0),
      k(0),
      jamming(false),
      successful_transmissions(0),
      interrupted_transmissions(0),
      dropped_frames(0),
      is_sending(false),
      current_frame_start_slot(0),
      frames_bytes_(frames_bytes),
      hol_index_(0)
{
}

bool Station::exponential_backoff()
{
    if (k < max_backoff_attempts)
    {
        ++k;
        std::uniform_int_distribution<int> dist(0, (1 << k) - 1);
        waiting_period = dist(rng);
        return false; // not dropped
    }
    // Exceeded Kmax: drop HOL frame
    k = 0;
    drop_period = 5; // cooldown
    ++dropped_frames;
    return true; // indicate drop
}

bool Station::should_transmit()
{
    if (frames_remaining() <= 0)
        return false;
    if (is_sending)
        return false;

    if (drop_period > 0)
    {
        --drop_period;
        return false;
    }

    if (waiting_period == 0 && !channel->busy)
    {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(rng) < p_persistence;
    }

    if (waiting_period > 0)
    {
        --waiting_period;
        return false;
    }

    if (channel->busy)
    {
        (void)exponential_backoff();
    }
    return false;
}

void Station::interrupt()
{
    channel->busy_delay = 0;
    channel->current_station_id.clear();
    jamming = true;
    is_sending = false;
    (void)exponential_backoff();
    ++interrupted_transmissions;
}

void Station::reset()
{
    waiting_period = 0;
    drop_period = 0;
    k = 0;
    jamming = false;
    successful_transmissions = 0;
    interrupted_transmissions = 0;
    dropped_frames = 0;
    is_sending = false;
    current_frame_start_slot = 0;
}

int Station::hol_frame_bytes() const
{
    if (hol_index_ >= frames_bytes_.size())
        return 0;
    return frames_bytes_[hol_index_];
}

void Station::advance_after_success(int now)
{
    if (hol_index_ < frames_bytes_.size())
    {
        ++hol_index_;
        if (hol_index_ < frames_bytes_.size())
        {
            current_frame_start_slot = now; // next frame starts waiting now
        }
    }
}

void Station::advance_after_drop(int now)
{
    if (hol_index_ < frames_bytes_.size())
    {
        ++hol_index_;
        if (hol_index_ < frames_bytes_.size())
        {
            current_frame_start_slot = now;
        }
    }
}

int Station::frames_remaining() const
{
    if (hol_index_ >= frames_bytes_.size())
        return 0;
    return static_cast<int>(frames_bytes_.size() - hol_index_);
}
