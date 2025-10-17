#ifndef SENDER_H
#define SENDER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "packet.h"

struct Feedback
{
    bool isACK;
    int seq;
};

class Sender
{
private:
    SOCKET sock;
    sockaddr_in receiverAddr;
    std::string srcMAC, dstMAC;
    double lossProb, errProb;
    int maxDelayMs, payloadSize, windowSize, crcType;
    std::string checksumScheme, inputFilename;
    double timeoutMs, estRTT, devRTT;
    size_t totalRetransmissions, totalBytesDelivered, totalPayloads;
    long long totalFramesSent, totalFrameBytesSent, total_ms;
    long long totalRetransmittedBytes, totalAckBytes;

    std::vector<double> rttSamples;
    std::unordered_map<int, long long> sendTimestamps;
    std::unordered_map<int, int> sendCounts;
    std::unordered_map<int, bool> acked;
    std::string mode;

    static long long now_ms();

    std::vector<unsigned char> Channel(const std::vector<unsigned char> &frame);
    std::vector<unsigned char> Framing(const std::vector<unsigned char> &payload, unsigned int seq_num);
    int fileSize(const std::string &path);

    void Timeout(double rttMs);
    int RecvACK(int waitMs, long long &recvTimeMs);
    std::vector<Feedback> RecvAllFeedbacks(int waitMs, long long &recvTimeMs);
    void tcpSend(const std::vector<unsigned char> &frame, bool isRetransmission);

    // Flow control protocols
    void sendStopAndWait(const std::vector<std::vector<unsigned char>> &payloads);
    void sendGoBackN(const std::vector<std::vector<unsigned char>> &payloads);
    void sendSelectiveRepeat(const std::vector<std::vector<unsigned char>> &payloads);

public:
    Sender(const std::string &serverIp, int serverPort, const std::string &m,
           int N, double loss_p, double err_p, int maxDelay,
           int payloadSize, int crcType, const std::string &checksumScheme,
           const std::string &inputFilename);
    ~Sender();

    void processFile();
    void printStats(const std::string &path);
};

#endif
