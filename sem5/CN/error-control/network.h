#ifndef NETWORK_H
#define NETWORK_H

#include "packet.h"
#include "utils.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class Network
{
    SOCKET sock;
    std::string error_type;

    void injectError(std::string &data);

public:
    Network(const std::string);
    ~Network();

    bool init();
    bool connectToServer(const Packet &pkt, Mode &mode); // using server header
    bool sendMessage(const Packet &pkt);
    void cleanup();
};

#endif // NETWORK_H