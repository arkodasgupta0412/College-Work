#include "utils.h"
using namespace std;

Mode getModeFromStr(const string &s)
{
    if (s == "CRC8")
        return Mode::CRC8;
    else if (s == "CRC10")
        return Mode::CRC10;
    else if (s == "CRC16")
        return Mode::CRC16;
    else if (s == "CRC32")
        return Mode::CRC32;
    else if (s == "CHECKSUM")
        return Mode::CHECKSUM;
    else
        return Mode::UNKNOWN;
}

string getStrFromMode(Mode &mode)
{
    if (mode == Mode::CRC8)
        return "CRC8";
    else if (mode == Mode::CRC10)
        return "CRC10";
    else if (mode == Mode::CRC16)
        return "CRC16";
    else if (mode == Mode::CRC32)
        return "CRC32";
    else if (mode == Mode::CHECKSUM)
        return "CHECKSUM";
    else
        return "UNKNOWN";
}

int isBinary(const string &data)
{
    for (char c : data)
    {
        if (c != '0' && c != '1')
            return 0;
    }
    return 1;
}
