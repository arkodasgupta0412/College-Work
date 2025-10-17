#include <windows.h>
#include "utils.h"
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")
using namespace std;

string bytesToBitString(const vector<unsigned char> &bytes)
{
    string s;
    s.reserve(bytes.size() * 8);
    for (unsigned char b : bytes)
    {
        for (int i = 7; i >= 0; --i)
            s.push_back(((b >> i) & 1) ? '1' : '0');
    }
    return s;
}

vector<unsigned char> bitStringToBytes(const string &bits)
{
    vector<unsigned char> out;
    size_t n = bits.size();
    size_t padded = ((n + 7) / 8) * 8;
    string b = bits;
    if (b.size() < padded)
        b.append(padded - b.size(), '0');
    for (size_t i = 0; i < b.size(); i += 8)
    {
        unsigned char val = 0;
        for (int j = 0; j < 8; ++j)
            val = (val << 1) | (b[i + j] - '0');
        out.push_back(val);
    }
    return out;
}

string getLocalMACAddress()
{
    PIP_ADAPTER_INFO adapterInfo;
    ULONG bufferSize = sizeof(IP_ADAPTER_INFO);
    string macAddress = "";

    // First call to get buffer size
    adapterInfo = (IP_ADAPTER_INFO *)malloc(bufferSize);
    if (GetAdaptersInfo(adapterInfo, &bufferSize) == ERROR_BUFFER_OVERFLOW)
    {
        free(adapterInfo);
        adapterInfo = (IP_ADAPTER_INFO *)malloc(bufferSize);
    }

    if (GetAdaptersInfo(adapterInfo, &bufferSize) == NO_ERROR)
    {
        PIP_ADAPTER_INFO adapter = adapterInfo;
        while (adapter)
        {
            // Skip loopback and tunnel adapters, get the first Ethernet/Wi-Fi adapter
            if (adapter->Type == MIB_IF_TYPE_ETHERNET || adapter->Type == IF_TYPE_IEEE80211)
            {
                char mac[18];
                snprintf(mac, sizeof(mac), "%02X:%02X:%02X:%02X:%02X:%02X",
                         adapter->Address[0], adapter->Address[1], adapter->Address[2],
                         adapter->Address[3], adapter->Address[4], adapter->Address[5]);
                macAddress = mac;
                break;
            }
            adapter = adapter->Next;
        }
    }

    free(adapterInfo);

    if (macAddress.empty())
    {
        macAddress = "00:1A:2B:3C:4D:5E";
    }

    return macAddress;
}

vector<unsigned char> macStringToBytes(const string &mac)
{
    vector<unsigned char> bytes;
    unsigned int values[6];

    if (sscanf(mac.c_str(), "%02X:%02X:%02X:%02X:%02X:%02X",
               &values[0], &values[1], &values[2],
               &values[3], &values[4], &values[5]) == 6)
    {
        for (int i = 0; i < 6; i++)
        {
            bytes.push_back(static_cast<unsigned char>(values[i]));
        }
    }
    else
    {
        bytes = {0x00, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E};
    }

    return bytes;
}