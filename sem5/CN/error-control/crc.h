#ifndef CRC_H
#define CRC_H

#include <string>

std::string xorStrings(const std::string &, const std::string &);
std::string mod2div(std::string, const std::string &);
std::string CRC(const std::string &, int, bool);

#endif // CRC_H