#include "CRC.h"
#include <string>
using namespace std;

string xorStrings(const string &a, const string &b)
{
    /* Note that b.length <= a.length as b will be the divisor */
    string result = "";
    for (int i = 0; i < b.length(); i++)
    {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string mod2div(string dividend, const string &divisor)
{
    int pick = divisor.size();
    string temp = dividend.substr(0, pick);

    while (pick < dividend.size())
    {
        if (temp[0] == '1')
            temp = xorStrings(divisor, temp) + dividend[pick];
        else
            temp = xorStrings(string(divisor.size(), '0'), temp) + dividend[pick];

        temp = temp.substr(1);
        pick++;
    }

    if (temp[0] == '1')
        temp = xorStrings(divisor, temp);
    else
        temp = xorStrings(string(divisor.size(), '0'), temp);

    return temp.substr(1);
}

string CRC(const string &frame, int crc_type, bool encode)
{
    const string CRC8 = "111010101", CRC10 = "11000110010", CRC16 = "11000000000000101", CRC32 = "100000100110000010001110110110111";
    string divisor;

    if (crc_type == 8)
        divisor = CRC8;
    else if (crc_type == 10)
        divisor = CRC10;
    else if (crc_type == 16)
        divisor = CRC16;
    else if (crc_type == 32)
        divisor = CRC32;

    int len = divisor.length();

    string dividend = frame;

    if (encode)
        dividend += string(len - 1, '0');

    string redundant_bits = mod2div(dividend, divisor);

    return redundant_bits;
}