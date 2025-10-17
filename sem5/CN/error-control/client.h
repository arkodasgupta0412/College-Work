#ifndef CLIENT_H
#define CLIENT_H

#include "packet.h"
#include "network.h"
#include "utils.h"
#include <string>
#include <vector>

class Client
{
    int port;
    std::string ip;
    Mode mode;

    std::string file_input;
    std::vector<std::string> frames, codewords;
    std::vector<Packet> data;

    void extractData(const std::string &);
    void createFrames(const int);
    void createCodewords();

public:
    Client(const std::string, const int, const std::string);
    ~Client();

    void createPackets(const std::string &, const int);
    bool sendPackets(Network &net);
};

#endif // CLIENT_H