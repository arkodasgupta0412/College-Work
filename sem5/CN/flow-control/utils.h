#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Converts a byte array into a string of '0' and '1' bits
std::string bytesToBitString(const std::vector<unsigned char> &bytes);

// Converts a string of '0' and '1' bits into a byte array
std::vector<unsigned char> bitStringToBytes(const std::string &bits);

std::string getLocalMACAddress();
std::vector<unsigned char> macStringToBytes(const std::string &mac);

#endif // UTILS_H
