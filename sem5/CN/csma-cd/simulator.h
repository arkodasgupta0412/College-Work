#pragma once
#include <fstream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include "station.h"
#include "channel.h"

class Simulator
{
public:
    Simulator(std::shared_ptr<Channel> ch,
              std::map<std::string, Station> &st,
              double time_seconds_cap,
              double collision_probability,
              std::mt19937 &rng);

    ~Simulator();

    void run();

    long long get_total_success_bytes() const { return total_success_bytes; }
    long long get_total_success_frames() const { return total_success_frames; }
    long long get_total_forwarding_delay_slots() const { return total_forwarding_delay_slots; }
    long long get_time_elapsed_slots() const { return time_elapsed_slots; }
    long long get_collision_events() const { return collision_events; }

private:
    std::shared_ptr<Channel> channel;
    std::map<std::string, Station> &stations;
    double simulation_time_cap;
    double collision_prob;
    std::mt19937 &rng;
    std::ofstream log_file;

    long long total_success_bytes;
    long long total_success_frames;
    long long total_forwarding_delay_slots;
    long long time_elapsed_slots;
    long long collision_events;

    int ongoing_frame_bytes; // size of the currently transmitting frame (bytes)

    bool all_done() const;
};
