#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include <bitset>
#include "simulator.h"

static int clamp_int(int v, int lo, int hi)
{
    if (v < lo)
        return lo;
    if (v > hi)
        return hi;
    return v;
}
static double clamp_double(double v, double lo, double hi)
{
    if (v < lo)
        return lo;
    if (v > hi)
        return hi;
    return v;
}

static std::vector<int> build_frames_from_line_bits(const std::string &line, int frame_bits)
{
    std::vector<int> frames_bytes;
    if (frame_bits <= 0)
        return frames_bytes;

    // Build a full bitstring from ASCII characters (8 bits per char)
    std::string bits;
    bits.reserve(line.size() * 8);
    for (std::size_t i = 0; i < line.size(); ++i)
    {
        unsigned char c = static_cast<unsigned char>(line[i]);
        std::bitset<8> b(c);
        bits += b.to_string(); // MSB first
    }

    // Split into frames of frame_bits; each frame's size in BYTES = ceil(bits_in_frame / 8)
    std::size_t pos = 0;
    while (pos < bits.size())
    {
        int remaining = static_cast<int>(bits.size() - pos);
        int take_bits = remaining < frame_bits ? remaining : frame_bits;
        int bytes_for_frame = (take_bits + 7) / 8;
        if (bytes_for_frame <= 0)
            bytes_for_frame = 1;
        frames_bytes.push_back(bytes_for_frame);
        pos += static_cast<std::size_t>(take_bits);
    }

    return frames_bytes;
}

int main()
{
    int num_stations = 0;
    double p_input = 0.0;
    int kmax = 0;
    int slot_time_ms = 1;
    double collision_prob = 0.0;
    int frame_size_bits = 0; // NEW

    std::cout << "Enter number of stations (<=15): ";
    std::cin >> num_stations;

    std::cout << "Enter p (0..1) for p-persistence: ";
    std::cin >> p_input;

    std::cout << "Enter K_max (max backoff attempts): ";
    std::cin >> kmax;

    std::cout << "Enter slot time (milliseconds): ";
    std::cin >> slot_time_ms;

    std::cout << "Enter collision probability (0..1): ";
    std::cin >> collision_prob;

    std::cout << "Enter FRAME SIZE (in bits): ";
    std::cin >> frame_size_bits;

    if (num_stations <= 0 || num_stations > 15)
    {
        std::cout << "Number of stations must be between 1 and 15.\n";
        return 1;
    }
    p_input = clamp_double(p_input, 0.0, 1.0);
    kmax = clamp_int(kmax, 0, 30);
    if (slot_time_ms <= 0)
        slot_time_ms = 1;
    collision_prob = clamp_double(collision_prob, 0.0, 1.0);
    if (frame_size_bits <= 0)
    {
        std::cout << "Frame size (bits) must be positive.\n";
        return 1;
    }

    // Channel params: bandwidth in BYTES per slot; Tp in slots
    const int bandwidth_bytes_per_slot = 100;
    const int Tp_slots = 1;

    const double slots_per_second = 1000.0 / static_cast<double>(slot_time_ms);
    const double channel_rate_bps = static_cast<double>(bandwidth_bytes_per_slot) * 8.0 * slots_per_second;

    // Load input.txt (15 lines max)
    std::ifstream in("input.txt");
    if (!in)
    {
        std::cout << "Could not open input.txt\n";
        return 1;
    }
    std::vector<std::string> lines;
    lines.reserve(15);
    std::string line;
    while (std::getline(in, line))
    {
        lines.push_back(line);
        if (lines.size() == 15)
            break;
    }
    in.close();

    // Prepare frames per station from its line (ASCII -> bits -> frames of frame_size_bits)
    std::random_device rd;
    unsigned seed = rd.entropy() ? rd() : 5489u;
    std::mt19937 rng(seed);

    std::shared_ptr<Channel> ch = std::make_shared<Channel>(bandwidth_bytes_per_slot, Tp_slots);

    std::cout << "\nStarting Simulation....\n\n";
    std::map<std::string, Station> stations;
    for (int i = 1; i <= num_stations; ++i)
    {
        std::string payload = (static_cast<std::size_t>(i - 1) < lines.size()) ? lines[static_cast<std::size_t>(i - 1)] : std::string();
        std::vector<int> frames_bytes = build_frames_from_line_bits(payload, frame_size_bits);

        std::string id = std::string("S") + std::to_string(i);
        stations.emplace(id, Station(id, p_input, kmax, frames_bytes, ch, rng));

        std::cout << "[FRAME-PREP] " << id << " -> payload_chars=" << payload.size()
                  << ", frames=" << frames_bytes.size() << "\n";
    }

    const double time_cap_seconds = 3600.0;
    Simulator sim(ch, stations, time_cap_seconds, collision_prob, rng);
    sim.run();

    long long success_bytes = sim.get_total_success_bytes();
    long long success_frames = sim.get_total_success_frames();
    long long time_slots = sim.get_time_elapsed_slots();
    long long delay_slots_sum = sim.get_total_forwarding_delay_slots();
    long long collisions = sim.get_collision_events();

    double throughput_bps = 0.0;
    double avg_delay_ms = 0.0;
    double efficiency = 0.0;

    if (time_slots > 0)
    {
        double throughput_bytes_per_slot = static_cast<double>(success_bytes) / static_cast<double>(time_slots);
        throughput_bps = throughput_bytes_per_slot * 8.0 * slots_per_second;
        efficiency = (bandwidth_bytes_per_slot > 0)
                         ? (throughput_bytes_per_slot / static_cast<double>(bandwidth_bytes_per_slot))
                         : 0.0;
    }
    if (success_frames > 0)
    {
        double avg_delay_slots = static_cast<double>(delay_slots_sum) / static_cast<double>(success_frames);
        avg_delay_ms = avg_delay_slots * static_cast<double>(slot_time_ms);
    }

    std::cout << std::fixed;
    std::cout << "\n=== Results (p=" << std::setprecision(2) << p_input << ") ===\n";
    std::cout << "Throughput (bps): " << std::setprecision(3) << throughput_bps << "\n";
    std::cout << "Forwarding delay (ms): " << std::setprecision(3) << avg_delay_ms << "\n";
    // std::cout << "Efficiency: " << std::setprecision(4) << efficiency << "\n";
    std::cout << "Number of collisions: " << collisions << "\n";

    return 0;
}
