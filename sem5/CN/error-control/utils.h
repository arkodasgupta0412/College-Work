#ifndef UTILS_H
#define UTILS_H

#include <string>

enum class Mode
{
    CRC8,
    CRC10,
    CRC16,
    CRC32,
    CHECKSUM,
    UNKNOWN
};

Mode getModeFromStr(const std::string &);
std::string getStrFromMode(Mode &mode);
int isBinary(const std::string &);

#endif // UTILS_H