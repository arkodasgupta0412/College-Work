#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <string>
#include <vector>

std::string onesComplement(std::string);
std::string binaryAdd(std::string, std::string, int);
std::string Checksum(std::vector<std::string> &, int);

#endif