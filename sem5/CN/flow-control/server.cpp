#include "server.h"
#include "utils.h"
#include "../asgmt1/crc.h"
#include "../asgmt1/checksum.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Receiver::Receiver(int port, const string &m, const string &sch, int N)
    : expectedSeq(0), mode(m), windowSize(N), scheme(sch), crcType(0)
{
    if (scheme.find("crc") == 0)
        crcType = stoi(scheme.substr(3));

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cerr << "WSAStartup failed\n";
        exit(1);
    }

    listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSock == INVALID_SOCKET)
    {
        cerr << "Socket creation failed\n";
        WSACleanup();
        exit(1);
    }

    ZeroMemory(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(listenSock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR ||
        listen(listenSock, 5) == SOCKET_ERROR)
    {
        cerr << "Bind/Listen failed\n";
        closesocket(listenSock);
        WSACleanup();
        exit(1);
    }

    cout << "Server listening on port " << port
         << " | Mode: " << mode
         << " | Window: " << windowSize
         << " | Scheme: " << scheme << endl;

    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);
    clientSock = accept(listenSock, (sockaddr *)&clientAddr, &clientSize);
    if (clientSock == INVALID_SOCKET)
    {
        cerr << "Accept failed\n";
        closesocket(listenSock);
        WSACleanup();
        exit(1);
    }

    srand((unsigned)time(NULL));
    cout << "Client connected\n";
}

Receiver::~Receiver()
{
    closesocket(clientSock);
    closesocket(listenSock);
    WSACleanup();
}

bool Receiver::Check(const vector<unsigned char> &frame)
{
    string bits = bytesToBitString(frame);
    if (scheme == "checksum")
    {
        // Split into payload + checksum
        string payload_bits = bits.substr(0, bits.size() - 16);
        string received_checksum = bits.substr(bits.size() - 16);

        vector<string> chunks;
        for (size_t i = 0; i < payload_bits.size(); i += 16)
        {
            string chunk = payload_bits.substr(i, 16);
            if (chunk.size() < 16)
                chunk.append(16 - chunk.size(), '0');
            chunks.push_back(chunk);
        }

        string sum(16, '0');
        for (auto &cw : chunks)
            sum = binaryAdd(sum, cw, 16);
        return (onesComplement(sum) == received_checksum);
    }
    else
    {
        string divisor;
        if (crcType == 8)
            divisor = "111010101";
        else if (crcType == 10)
            divisor = "11000110010";
        else if (crcType == 16)
            divisor = "11000000000000101";
        else if (crcType == 32)
            divisor = "100000100110000010001110110110111";

        string remainder = mod2div(bits, divisor);
        return remainder.find('1') == string::npos;
    }
}

void Receiver::SendACK(int seq)
{
    if ((double)rand() / RAND_MAX < ackLossProb)
    {
        cout << "ACK lost for frame " << seq << endl;
        return;
    }
    string ack = "ACK" + to_string(seq);
    send(clientSock, ack.c_str(), ack.size(), 0);
    cout << "Sent ACK" << seq << endl;
}

void Receiver::SendNAK(int seq)
{
    if ((double)rand() / RAND_MAX < nakLossProb)
    {
        cout << "NAK lost for frame " << seq << endl;
        return;
    }
    string nak = "NAK" + to_string(seq);
    send(clientSock, nak.c_str(), nak.size(), 0);
    cout << "Sent NAK" << seq << endl;
}

void Receiver::processSW(const vector<unsigned char> &frame, unsigned char seq)
{
    if (Check(frame))
    {
        cout << "Accepted frame " << (int)seq << endl;
        SendACK(seq);
        expectedSeq = (expectedSeq + 1) % 2;
    }
    else
    {
        cout << "Corrupted frame " << (int)seq << endl;
        SendACK((expectedSeq + 1) % 2); // re-ACK last good
    }
}

void Receiver::processGBN(const vector<unsigned char> &frame, unsigned char seq)
{
    if (Check(frame) && seq == expectedSeq)
    {
        cout << "Accepted frame " << (int)seq << endl;
        expectedSeq = (expectedSeq + 1) % 256;
    }
    else
    {
        cout << "Rejected frame " << (int)seq
             << ", expected " << (int)expectedSeq << endl;
    }
    SendACK(expectedSeq);
}

void Receiver::processSR(const vector<unsigned char> &frame, unsigned char seq)
{
    if (!Check(frame))
    {
        cout << "Corrupted frame " << (int)seq << endl;
        SendNAK(seq);
        return;
    }

    cout << "Received frame " << (int)seq << endl;
    SendACK(seq);

    if (seq >= expectedSeq && seq < expectedSeq + windowSize)
    {
        buffer[seq] = frame;
        while (buffer.count(expectedSeq))
        {
            cout << "Delivered frame " << (int)expectedSeq << endl;
            buffer.erase(expectedSeq);
            expectedSeq = (expectedSeq + 1) % 256;
        }
    }
    else
    {
        cout << "Frame " << (int)seq << " outside window" << endl;
    }
}

void Receiver::Run()
{
    char buf[2048];
    while (true)
    {
        int bytes = recv(clientSock, buf, sizeof(buf), 0);
        if (bytes <= 0)
        {
            cout << "Connection closed\n";
            break;
        }
        vector<unsigned char> frame(buf, buf + bytes);
        unsigned char seq = frame[14]; // seqNum is 15th byte
        if (mode == "SW")
            processSW(frame, seq);
        else if (mode == "GBN")
            processGBN(frame, seq);
        else if (mode == "SR")
            processSR(frame, seq);
    }
}
