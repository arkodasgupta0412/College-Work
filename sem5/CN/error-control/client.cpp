#include "client.h"
#include "utils.h"
#include "error.h"
#include "network.h"
#include "packet.h"
#include "crc.h"
#include "checksum.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
using namespace std;

const string clientIP = "127.0.0.1";
const int clientPort = 8000;
const string serverIP = "127.0.0.1";
const int serverPort = 8080;

// CLIENT CONSTRUCTOR
Client::Client(const string ip, const int port, const string mode)
{
    this->ip = ip;
    this->port = port;
    this->mode = getModeFromStr(mode);
}

// CLIENT DESTRUCTOR
Client::~Client() {}

void Client::extractData(const string &path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        cout << "Error opening file: " << path << endl;
        file_input = "";
        return;
    }

    string data;
    getline(file, data);
    Sleep(1000);
    file.close();

    file_input = data;

    return;
}

void Client::createFrames(const int frameSize = 8)
{
    string padded_data = file_input;
    int rem = file_input.length() % frameSize;

    // added padding accordingly
    if (rem != 0)
    {
        int padding = frameSize - rem;
        padded_data += string(padding, '0');
    }

    vector<string> frames;
    for (int i = 0; i < padded_data.length(); i += frameSize)
    {
        frames.push_back(padded_data.substr(i, frameSize));
        Sleep(200);
    }

    this->frames = frames;
    cout << frames.size() << " frames generated ... \n";
}

void Client::createCodewords()
{
    int len = frames.size();
    vector<string> codewords;
    bool encode = true;

    if (mode == Mode::CRC8)
    {
        for (int i = 0; i < frames.size(); i++)
        {
            string redundant_bits = CRC(frames[i], 8, encode);
            string codeword = frames[i] + redundant_bits;
            codewords.push_back(codeword);
            Sleep(200);
        }
    }
    else if (mode == Mode::CRC10)
    {
        for (int i = 0; i < frames.size(); i++)
        {
            string redundant_bits = CRC(frames[i], 10, encode);
            string codeword = frames[i] + redundant_bits;
            codewords.push_back(codeword);
            Sleep(200);
        }
    }
    else if (mode == Mode::CRC16)
    {
        for (int i = 0; i < frames.size(); i++)
        {
            string redundant_bits = CRC(frames[i], 16, encode);
            string codeword = frames[i] + redundant_bits;
            codewords.push_back(codeword);
            Sleep(200);
        }
    }
    else if (mode == Mode::CRC32)
    {
        for (int i = 0; i < frames.size(); i++)
        {
            string redundant_bits = CRC(frames[i], 32, encode);
            string codeword = frames[i] + redundant_bits;
            codewords.push_back(codeword);
            Sleep(200);
        }
    }
    else
    {
        int framesize = frames[0].length();
        codewords = frames;

        string checksum = Checksum(codewords, framesize);
        cout << "Checksum: " << checksum << "\n";
        codewords.push_back(checksum);

        // keep an end marker -> #
        codewords.push_back("#");
        Sleep(300);
    }

    this->codewords = codewords;
    cout << codewords.size() << " codewords generated ... \n";

    return;
}

void Client::createPackets(const string &path, const int frameSize)
{
    extractData(path);
    createFrames(frameSize);
    createCodewords();

    int len = codewords.size();
    vector<Packet> packets;

    for (int i = 0; i < len; i++)
    {
        Packet p(codewords[i], clientIP, serverIP, clientPort, serverPort);
        packets.push_back(p);
        Sleep(400);
    }

    this->data = packets;
    cout << packets.size() << " packets created ... \n";

    return;
}

bool Client::sendPackets(Network &net)
{
    if (data.empty())
    {
        cout << "No packets to send.\n";
        return false;
    }

    // Connect to server ip+port using network and send HandShaking Mode
    if (!net.connectToServer(data.front(), mode))
    {
        cout << "Network connect failed.\n";
        return false;
    }

    Sleep(700);
    for (const auto &pkt : data)
    {
        if (pkt.getData().length() > 1)
            cout << "[Client] Packet sent: " << pkt.getData() << " (";

        if (!net.sendMessage(pkt))
        {
            cout << "Failed)\n";
            return false;
        }

        if (pkt.getData().length() > 1)
            cout << ")\n";

        Sleep(2000);
    }
    return true;
}

int main(int argc, char *argv[])
{
    Network net(argv[4]);
    if (!net.init())
        return 1;

    Client client(clientIP, clientPort, argv[1]);
    client.createPackets(argv[2], stoi(argv[3]));
    client.sendPackets(net);

    net.cleanup();

    return 0;
}