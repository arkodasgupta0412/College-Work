#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <fstream>
#include <memory>

// --- Simulation Constants ---
constexpr int BANDWIDTH = 1000;          // Channel bandwidth in bits per millisecond
constexpr int PROPAGATION_DELAY = 5;     // Propagation delay (Tp) in milliseconds
constexpr int FRAME_SIZE = 1200;         // Frame size in bits
constexpr int MAX_BACKOFF_ATTEMPTS = 15; // Kmax for exponential backoff