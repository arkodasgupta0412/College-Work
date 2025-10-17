#pragma once
#include <memory>
#include <random>
#include <string>
#include <vector>
#include "channel.h"

class Station
{
public:
    Station(std::string station_id,
            double p,
            int kmax,
            const std::vector<int> &frames_bytes,
            std::shared_ptr<Channel> ch,
            std::mt19937 &random_generator);

    // Backoff logic; returns true if current HOL frame is dropped (exceeded Kmax)
    bool exponential_backoff();

    // Should attempt to transmit this slot (p-persistent)
    bool should_transmit();

    // Interrupt in-flight transmission (collision while sending)
    void interrupt();

    // Reset counters (does not change prepared frames)
    void reset();

    // Head-of-line frame size (bytes), or 0 if none
    int hol_frame_bytes() const;

    // Advance queue after successful transmission
    void advance_after_success(int now);

    // Advance queue after drop due to Kmax
    void advance_after_drop(int now);

    // How many frames are left to send (including HOL)
    int frames_remaining() const;

    // Public fields used by simulator/logs
    std::shared_ptr<Channel> channel;
    double p_persistence;
    std::mt19937 &rng;
    std::string id;

    int max_backoff_attempts;
    int waiting_period; // slots
    int drop_period;    // slots
    int k;              // current backoff exponent
    bool jamming;

    int successful_transmissions;
    int interrupted_transmissions;
    int dropped_frames;
    bool is_sending;

    int current_frame_start_slot; // slot when HOL started waiting

private:
    std::vector<int> frames_bytes_; // per-frame sizes in BYTES
    std::size_t hol_index_;         // index of head-of-line frame
};
