#include "client.h"
#include "utils.h"
#include "packet.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <iomanip>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;
using Clock = chrono::steady_clock;
using ms = chrono::milliseconds;

extern void injectSingleBitError(string &data);
extern void injectTwoBitError(string &data);
extern void injectBurstError(string &data);
extern void injectOddError(string &data);
extern string CRC(const string &frame, int crc_type, bool encode);
extern string Checksum(vector<string> &codewords, int frameSize);

const int INITIAL_TIMEOUT_MS = 2000;
const int MAX_CHANNEL_DELAY_MS = 400;

long long Sender::now_ms()
{
    return chrono::duration_cast<ms>(Clock::now().time_since_epoch()).count();
}

Sender::Sender(const string &serverIp, int serverPort, const string &m,
               int N, double loss_p, double err_p, int maxDelay,
               int payloadSize, int crcType, const string &checksumScheme,
               const string &inputFilename)
    : lossProb(loss_p), errProb(err_p), maxDelayMs(maxDelay),
      payloadSize(payloadSize), windowSize(N), crcType(crcType),
      checksumScheme(checksumScheme), inputFilename(inputFilename),
      timeoutMs(INITIAL_TIMEOUT_MS), estRTT(INITIAL_TIMEOUT_MS),
      devRTT(INITIAL_TIMEOUT_MS / 2.0), totalFramesSent(0),
      totalRetransmissions(0), totalBytesDelivered(0), total_ms(0),
      totalRetransmittedBytes(0), totalAckBytes(0), totalFrameBytesSent(0), mode(m)
{

    // Setup MACs
    srcMAC = getLocalMACAddress();
    dstMAC = srcMAC;

    // Setup socket
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cerr << "WSAStartup failed" << endl;
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        cerr << "Socket creation failed" << endl;
        WSACleanup();
        exit(1);
    }

    ZeroMemory(&receiverAddr, sizeof(receiverAddr));
    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(serverPort);
    receiverAddr.sin_addr.s_addr = inet_addr(serverIp.c_str());

    if (connect(sock, (sockaddr *)&receiverAddr, sizeof(receiverAddr)) == SOCKET_ERROR)
    {
        cerr << "Connection failed" << endl;
        closesocket(sock);
        WSACleanup();
        exit(1);
    }

    srand((unsigned)time(NULL));
    cout << "Connected to " << serverIp << ":" << serverPort << " | Mode: " << mode << endl;
}

Sender::~Sender()
{
    closesocket(sock);
    WSACleanup();
}

vector<unsigned char> Sender::Framing(const vector<unsigned char> &payload, unsigned int seq_num)
{
    auto srcMACBytes = macStringToBytes(srcMAC);
    auto dstMACBytes = macStringToBytes(dstMAC);

    Packet pkt(srcMACBytes, dstMACBytes, payload, (unsigned char)seq_num,
               checksumScheme, crcType);

    return pkt.toBytes();
}

vector<unsigned char> Sender::Channel(const vector<unsigned char> &frame)
{
    if ((double)rand() / RAND_MAX < lossProb)
    {
        cout << "Frame dropped by channel" << endl;
        return {};
    }

    string bits = bytesToBitString(frame);
    if ((double)rand() / RAND_MAX < errProb)
    {
        switch (rand() % 4)
        {
        case 0:
            injectSingleBitError(bits);
            break;
        case 1:
            injectTwoBitError(bits);
            break;
        case 2:
            injectBurstError(bits);
            break;
        case 3:
            injectOddError(bits);
            break;
        }
        cout << "Bit errors injected into frame " << endl;
    }

    Sleep(rand() % (maxDelayMs + 1));

    return bitStringToBytes(bits);
}

void Sender::Timeout(double rttMs)
{
    timeoutMs = rttMs * 2;

    if (timeoutMs < 1000)
        timeoutMs = 1000;

    if (timeoutMs > 10000)
        timeoutMs = 10000;

    rttSamples.push_back(rttMs);
}

int Sender::RecvACK(int waitMs, long long &recvTimeMs)
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);

    timeval tv;
    tv.tv_sec = waitMs / 1000;
    tv.tv_usec = (waitMs % 1000) * 1000;

    if (select(0, &readfds, NULL, NULL, &tv) <= 0)
        return -1;

    char buf[128];
    int bytes = recv(sock, buf, sizeof(buf) - 1, 0);
    if (bytes <= 0)
        return -1;

    totalAckBytes += bytes;
    buf[bytes] = '\0';
    string ack(buf, bytes);
    recvTimeMs = now_ms();

    if (ack.find("ACK") == 0 && ack.size() >= 4)
    {
        try
        {
            return stoi(ack.substr(3)) & 0xFF;
        }
        catch (...)
        {
            return -1;
        }
    }
    return -1;
}

vector<Feedback> Sender::RecvAllFeedbacks(int waitMs, long long &recvTimeMs)
{
    vector<Feedback> feedbacks;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);

    timeval tv;
    tv.tv_sec = waitMs / 1000;
    tv.tv_usec = (waitMs % 1000) * 1000;

    if (select(0, &readfds, NULL, NULL, &tv) <= 0)
        return feedbacks;

    char buf[512];
    int bytes = recv(sock, buf, sizeof(buf) - 1, 0);
    if (bytes <= 0)
        return feedbacks;

    totalAckBytes += bytes;
    buf[bytes] = '\0';
    recvTimeMs = now_ms();
    string s(buf, bytes);

    size_t pos = 0;
    while (pos < s.size())
    {
        if (s.compare(pos, 3, "ACK") == 0)
        {
            pos += 3;
            size_t start = pos;
            while (pos < s.size() && isdigit(s[pos]))
                pos++;
            feedbacks.push_back({true, stoi(s.substr(start, pos - start)) & 0xFF});
        }
        else if (s.compare(pos, 3, "NAK") == 0)
        {
            pos += 3;
            size_t start = pos;
            while (pos < s.size() && isdigit(s[pos]))
                pos++;
            feedbacks.push_back({false, stoi(s.substr(start, pos - start)) & 0xFF});
        }
        else
            pos++;
    }
    return feedbacks;
}

void Sender::tcpSend(const vector<unsigned char> &frame, bool isRetransmission = false)
{
    if (frame.empty())
        return;
    send(sock, (const char *)frame.data(), frame.size(), 0);
    totalFramesSent++;
    totalFrameBytesSent += frame.size();
    if (isRetransmission)
        totalRetransmittedBytes += frame.size();
}

void Sender::sendStopAndWait(const vector<vector<unsigned char>> &payloads)
{
    int n = payloads.size();
    int absIdx = 0;
    unsigned int seq = 0;
    acked.clear();

    while (absIdx < n)
    {
        vector<unsigned char> frame = Framing(payloads[absIdx], seq);
        vector<unsigned char> out = Channel(frame);
        long long sent_ms = now_ms();
        sendTimestamps[absIdx] = sent_ms;
        sendCounts[absIdx]++;

        if (!out.empty())
            tcpSend(out, false);
        else
            cout << "Frame " << absIdx << " dropped" << endl;

        long long recvTime = 0;
        int ack = RecvACK(timeoutMs, recvTime);
        if (ack == -1)
        {
            cout << "Timeout for frame " << absIdx << ", retransmitting..." << endl;
            totalRetransmissions++;
            continue;
        }

        if (ack == seq)
        {
            if (!acked[absIdx])
            {
                acked[absIdx] = true;
                double rtt = (recvTime - sent_ms);
                Timeout(rtt);
                totalBytesDelivered += payloads[absIdx].size();
                totalPayloads++;
                cout << "RTT for frame " << absIdx << ": " << rtt << " ms" << endl;
            }
            cout << "ACK" << ack << " received for frame " << absIdx << endl;
            absIdx++;
            seq = (seq + 1) % 2;
        }

        else
        {
            cout << "Unexpected ACK" << ack << ", expecting ACK" << seq << endl;
        }
    }
}

void Sender::sendGoBackN(const vector<vector<unsigned char>> &payloads)
{
    int n = payloads.size();
    int base = 0;
    int nextSeq = 0;
    acked.clear();

    while (base < n)
    {
        // send as many as window allows
        while (nextSeq < n && nextSeq < base + windowSize)
        {
            unsigned int seq_mod = nextSeq % 256;
            vector<unsigned char> frame = Framing(payloads[nextSeq], seq_mod);
            vector<unsigned char> out = Channel(frame);
            sendTimestamps[nextSeq] = now_ms();
            sendCounts[nextSeq]++;

            if (!out.empty())
            {
                tcpSend(out, false);
                cout << "Sent frame " << nextSeq << " (seq=" << seq_mod << ")" << endl;
            }
            else
            {
                cout << "Frame " << nextSeq << " dropped" << endl;
            }
            nextSeq++;
        }

        // grouped print showing all frames in the current window were sent
        cout << "Sent window frames [" << base << " .. " << (nextSeq - 1) << "]" << endl;

        long long recvTime = 0;
        int ack_mod = RecvACK(timeoutMs, recvTime);
        if (ack_mod == -1)
        {
            cout << "Timeout, retransmitting window " << base << " to " << nextSeq - 1 << endl;
            totalRetransmissions += (nextSeq - base);
            for (int i = base; i < nextSeq; i++)
            {
                unsigned int seq_mod = i % 256;
                vector<unsigned char> frame = Framing(payloads[i], seq_mod);
                vector<unsigned char> out = Channel(frame);
                sendTimestamps[i] = now_ms();
                sendCounts[i]++;
                if (!out.empty())
                    tcpSend(out, true);
            }
            continue;
        }

        int base_mod = base % 256;
        int ackedCount = (ack_mod - base_mod + 256) % 256;
        if (ackedCount == 0)
        {
            cout << "No progress ACK " << ack_mod << ", retransmitting window" << endl;
            for (int i = base; i < nextSeq; i++)
            {
                unsigned int seq_mod = i % 256;
                vector<unsigned char> frame = Framing(payloads[i], seq_mod);
                vector<unsigned char> out = Channel(frame);
                sendTimestamps[i] = now_ms();
                sendCounts[i]++;
                totalRetransmissions++;
                if (!out.empty())
                    tcpSend(out, true);
            }
            continue;
        }

        int actualAcked = min(ackedCount, nextSeq - base);
        cout << "Cumulative ACK " << ack_mod << " for up to " << actualAcked << " frames" << endl;

        // For each actually ACKed frame, update RTT and stats and print RTT
        long long nowRecvTime = recvTime;
        for (int i = 0; i < actualAcked; i++)
        {
            int idx = base + i;
            if (!acked[idx])
            {
                if (sendTimestamps.count(idx))
                {
                    double rtt = (double)(nowRecvTime - sendTimestamps[idx]);
                    Timeout(rtt);
                    cout << "RTT for frame " << idx << ": " << rtt << " ms" << endl;
                }
                totalBytesDelivered += payloads[idx].size();
                totalPayloads++;
                acked[idx] = true;
            }
        }

        base += actualAcked;
    }
}

void Sender::sendSelectiveRepeat(const vector<vector<unsigned char>> &payloads)
{
    int n = payloads.size();
    int base = 0;
    int nextSeq = 0;

    acked.clear();
    sendCounts.clear();
    sendTimestamps.clear();
    unordered_map<int, int> seqToAbsIdx; // maps seq_mod → absIdx

    while (base < n)
    {
        // Send frames within the window
        while (nextSeq < n && nextSeq < base + windowSize)
        {
            if (!sendCounts[nextSeq]) // not yet sent
            {
                unsigned int seq_mod = nextSeq % 256;
                vector<unsigned char> frame = Framing(payloads[nextSeq], seq_mod);
                vector<unsigned char> out = Channel(frame);
                sendTimestamps[nextSeq] = now_ms();
                sendCounts[nextSeq]++;

                if (!out.empty())
                {
                    tcpSend(out, false);
                    cout << "Sent frame " << nextSeq
                         << " (seq=" << seq_mod << ")" << endl;
                }
                else
                {
                    cout << "Frame " << nextSeq << " dropped by channel" << endl;
                }

                seqToAbsIdx[seq_mod] = nextSeq;
            }
            nextSeq++;
        }

        // Print current window status
        cout << "Window [" << base << " .. " << min(nextSeq - 1, n - 1) << "] in-flight" << endl;

        long long recvTime = 0;
        auto feedbacks = RecvAllFeedbacks(timeoutMs, recvTime);

        if (!feedbacks.empty())
        {
            for (auto fb : feedbacks)
            {
                if (seqToAbsIdx.count(fb.seq))
                {
                    int absIdx = seqToAbsIdx[fb.seq];
                    if (absIdx < n)
                    {
                        if (fb.isACK) // ACK received
                        {
                            if (!acked[absIdx])
                            {
                                acked[absIdx] = true;
                                if (sendTimestamps.count(absIdx))
                                {
                                    double rtt = recvTime - sendTimestamps[absIdx];
                                    Timeout(rtt);
                                    cout << "ACK" << fb.seq
                                         << " → Frame " << absIdx
                                         << " delivered | RTT = " << rtt << " ms" << endl;
                                }
                                totalBytesDelivered += payloads[absIdx].size();
                                totalPayloads++;
                            }
                        }
                        else // NAK received
                        {
                            cout << "NAK" << fb.seq
                                 << " → Retransmitting frame " << absIdx << endl;

                            unsigned int seq_mod = absIdx % 256;
                            vector<unsigned char> frame = Framing(payloads[absIdx], seq_mod);
                            vector<unsigned char> out = Channel(frame);
                            sendTimestamps[absIdx] = now_ms();
                            sendCounts[absIdx]++;
                            totalRetransmissions++;
                            if (!out.empty())
                                tcpSend(out, true);
                        }
                    }
                }
            }

            // Slide base forward (deliver in order)
            while (base < n && acked[base])
                base++;
        }
        else
        {
            // Timeout check for unacked frames
            long long now = now_ms();
            for (int i = base; i < min(n, base + windowSize); i++)
            {
                if (!acked[i] && sendTimestamps.count(i))
                {
                    if (now - sendTimestamps[i] > timeoutMs)
                    {
                        unsigned int seq_mod = i % 256;
                        vector<unsigned char> frame = Framing(payloads[i], seq_mod);
                        vector<unsigned char> out = Channel(frame);
                        sendTimestamps[i] = now_ms();
                        sendCounts[i]++;
                        totalRetransmissions++;
                        if (!out.empty())
                            tcpSend(out, true);
                        cout << "Timeout → Retransmitted frame " << i
                             << " (seq=" << seq_mod << ")" << endl;
                    }
                }
            }
        }
    }
}

void Sender::processFile()
{
    ifstream fin(inputFilename, ios::binary);
    if (!fin)
    {
        cerr << "Cannot open input file: " << inputFilename << endl;
        return;
    }

    vector<vector<unsigned char>> payloads;
    while (!fin.eof())
    {
        vector<unsigned char> buf(payloadSize);
        fin.read((char *)buf.data(), payloadSize);
        int got = fin.gcount();
        if (got <= 0)
            break;
        buf.resize(got);
        payloads.push_back(buf);
    }
    fin.close();

    if (payloads.empty())
    {
        cout << "No data to send" << endl;
        return;
    }

    sendTimestamps.clear();
    sendCounts.clear();
    acked.clear();

    // cout << "Starting transmission of " << payloads.size() << " frames..." << endl;
    long long start_ms = now_ms();

    if (mode == "SW")
        sendStopAndWait(payloads);
    else if (mode == "GBN")
        sendGoBackN(payloads);
    else if (mode == "SR")
        sendSelectiveRepeat(payloads);
    else
        cerr << "Invalid mode: " << mode << endl;

    total_ms = now_ms() - start_ms;
    cout << "Transmission completed in " << total_ms << " ms" << endl;
}

int Sender::fileSize(const string &path)
{
    ifstream fin(path, ios::binary | ios::ate);
    if (!fin)
    {
        cerr << "Cannot open file: " << path << endl;
        return -1;
    }
    return (int)fin.tellg();
}

void Sender::printStats(const string &path)
{
    const int TCP_IP_OVERHEAD = 40;
    double efficiency = 0.0;
    if (totalFrameBytesSent + totalFramesSent * TCP_IP_OVERHEAD + totalAckBytes > 0)
    {
        efficiency = (double)(fileSize(path) / (double)payloadSize) / totalFramesSent;
    }

    // RTT stats (collected during Timeout() updates into rttSamples)
    double avgRTT = 0.0, minRTT = 1e9, maxRTT = -1e9;
    if (!rttSamples.empty())
    {
        double sum = 0.0;
        for (double rtt : rttSamples)
        {
            sum += rtt;
            minRTT = min(minRTT, rtt);
            maxRTT = max(maxRTT, rtt);
        }
        avgRTT = sum / rttSamples.size();
    }
    else
    {
        minRTT = maxRTT = avgRTT = 0.0;
    }

    cout << "\n=== TRANSMISSION STATISTICS ===" << endl;
    cout << "Frames sent: " << totalFramesSent << endl;
    // cout << "Payload delivered: " << totalBytesDelivered << " bytes" << endl;
    cout << "Retransmissions: " << totalRetransmissions << endl;

    // cout << fixed << setprecision(2);
    cout << "Efficiency: " << efficiency * 100 << "%" << endl;

    cout << "RTT (ms): avg=" << avgRTT
         << " | min=" << minRTT
         << " | max=" << maxRTT << endl;
}
