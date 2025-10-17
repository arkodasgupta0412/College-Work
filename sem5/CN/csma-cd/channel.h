#pragma once
#include <string>

struct Channel
{
    bool busy;
    int busy_delay;   // slots until channel becomes BUSY after acquisition
    int finish_delay; // slots remaining for current frame to finish
    int Tp;           // propagation delay in slots
    int bandwidth;    // bytes per slot
    std::string current_station_id;

    Channel(); // default: safe baseline
    Channel(int bandwidth_bytes_per_slot, int propagation_delay_slots);
};
