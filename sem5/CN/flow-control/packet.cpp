#include "packet.h"
#include "utils.h"
#include "../asgmt1/crc.h"
#include "../asgmt1/checksum.h"
using namespace std;

Packet::Packet(const vector<unsigned char> &src, const vector<unsigned char> &dst,
               const vector<unsigned char> &data, unsigned char seq, const string &scheme, int crcType)
    : srcMAC(src), dstMAC(dst), seqNum(seq)
{

    payload = data;
    length = payload.size();

    // build frame without FCS
    vector<unsigned char> temp;
    temp.insert(temp.end(), srcMAC.begin(), srcMAC.end());
    temp.insert(temp.end(), dstMAC.begin(), dstMAC.end());
    temp.push_back((length >> 8) & 0xFF);
    temp.push_back(length & 0xFF);
    temp.push_back(seqNum);
    temp.insert(temp.end(), payload.begin(), payload.end());

    string bits = bytesToBitString(temp);

    string redundant;
    if (scheme == "checksum")
    {
        vector<string> chunks;
        for (size_t i = 0; i < bits.size(); i += 16)
        {
            chunks.push_back(bits.substr(i, min(16UL, (unsigned long)bits.size() - i)));
        }
        redundant = Checksum(chunks, 16);
    }
    else
    {
        redundant = CRC(bits, crcType, true);
    }

    fcs = bitStringToBytes(redundant);
}

vector<unsigned char> Packet::toBytes() const
{
    vector<unsigned char> frame;
    frame.insert(frame.end(), srcMAC.begin(), srcMAC.end());
    frame.insert(frame.end(), dstMAC.begin(), dstMAC.end());
    frame.push_back((length >> 8) & 0xFF);
    frame.push_back(length & 0xFF);
    frame.push_back(seqNum);
    frame.insert(frame.end(), payload.begin(), payload.end());
    frame.insert(frame.end(), fcs.begin(), fcs.end());

    return frame;
}
