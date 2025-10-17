#ifndef RECEIVER_H
#define RECEIVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "packet.h"

class Receiver
{
private:
    SOCKET listenSock, clientSock;
    sockaddr_in serverAddr;

    unsigned char expectedSeq;
    std::string mode;
    int windowSize;
    std::string scheme;
    int crcType;

    std::unordered_map<int, std::vector<unsigned char>> buffer;

    double ackLossProb = 0.02; // probability ACK is lost
    double nakLossProb = 0.1;  // probability NAK is lost

    bool Check(const std::vector<unsigned char> &frame);
    void SendACK(int seq);
    void SendNAK(int seq);

    // Protocol handlers
    void processSW(const std::vector<unsigned char> &frame, unsigned char seq);
    void processGBN(const std::vector<unsigned char> &frame, unsigned char seq);
    void processSR(const std::vector<unsigned char> &frame, unsigned char seq);

public:
    Receiver(int port, const std::string &m, const std::string &sch, int N = 1);
    ~Receiver();

    void Run();
};

#endif
