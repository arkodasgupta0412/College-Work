#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "utils.h"
#include "packet.h"

#pragma comment(lib, "Ws2_32.lib")

class Server
{
    SOCKET serverSock;
    SOCKET clientSock;
    std::string ip;
    int port;
    Mode mode;

public:
    Server(const std::string &ip, int port);
    ~Server();

    bool init();
    bool start();
    bool acceptClient();
    bool receiveHandshake();
    bool receivePacket(std::string &);
    void processPacket(const Packet &pkt);
    void cleanup();
};

#endif // SERVER_H
