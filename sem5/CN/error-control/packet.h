#ifndef PACKET_H
#define PACKET_H

#include <string>

struct IPHeader
{
    std::string ClientIP;
    std::string ServerIP;
};

struct TCPHeader
{
    int ClientPort;
    int ServerPort;
};

class Packet
{
    std::string data;
    IPHeader ipHeader;
    TCPHeader tcpHeader;

public:
    Packet(std::string _data, std::string _cIP, std::string _sIP, int _cPort, int _sPort);
    ~Packet();

    // Accessors
    const std::string &getData() const { return data; }
    const std::string &getClientIP() const { return ipHeader.ClientIP; }
    const std::string &getServerIP() const { return ipHeader.ServerIP; }
    int getClientPort() const { return tcpHeader.ClientPort; }
    int getServerPort() const { return tcpHeader.ServerPort; }

    // FORMAT: "cIP:cPort->sIP:sPort|<payload>"
    std::string serialize() const;

    // cIP:cPort->sIP:sPort|<payload> -> Packet object
    static Packet deserialize(const std::string &);
};

#endif // PACKET_H
