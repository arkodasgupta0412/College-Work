#include "checksum.h"
#include <string>
#include <vector>
using namespace std;

string binaryAdd(string a, string b, int size)
{
    int carry = 0;
    string result(size, '0');

    // add bit by bit from right to left
    for (int i = size - 1; i >= 0; i--)
    {
        int bitA = a[i] - '0';
        int bitB = b[i] - '0';
        int sum = bitA + bitB + carry;
        result[i] = (sum % 2) + '0';
        carry = sum / 2;
    }

    // wrap carry until no carry is left
    while (carry)
    {
        for (int i = size - 1; i >= 0 && carry; i--)
        {
            int bit = result[i] - '0';
            int sum = bit + carry;
            result[i] = (sum % 2) + '0';
            carry = sum / 2;
        }
    }

    return result;
}

string onesComplement(string s)
{
    string t = "";
    for (int i = 0; i < s.length(); i++)
    {
        t.push_back(s[i] == '0' ? '1' : '0');
    }
    return t;
}

string Checksum(vector<string> &codewords, int frameSize)
{
    string sum(frameSize, '0');
    for (auto &cw : codewords)
    {
        sum = binaryAdd(sum, cw, frameSize);
    }

    string checksum = onesComplement(sum);

    return checksum;
}