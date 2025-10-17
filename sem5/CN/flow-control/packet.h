#ifndef PACKET_H
#define PACKET_H

#include <vector>
#include <string>

class Packet
{
public:
    std::vector<unsigned char> srcMAC;
    std::vector<unsigned char> dstMAC;
    unsigned short length;
    unsigned char seqNum;
    std::vector<unsigned char> payload;
    std::vector<unsigned char> fcs;

    Packet(const std::vector<unsigned char> &src,
           const std::vector<unsigned char> &dst,
           const std::vector<unsigned char> &data,
           unsigned char seq,
           const std::string &scheme,
           int crcType);

    std::vector<unsigned char> toBytes() const;
};

#endif
