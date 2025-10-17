#include "network.h"
#include "utils.h"
#include "error.h"
#include "packet.h"
#include <iostream>
#include <windows.h>
using namespace std;

void Network::injectError(string &data)
{
    if (error_type == "single")
        injectSingleBitError(data);

    else if (error_type == "double")
        injectTwoBitError(data);

    else if (error_type == "burst")
        injectBurstError(data);

    else if (error_type == "odd")
        injectOddError(data);

    else
    {
        cout << "Unknown error type: " << error_type << endl;
        exit(1);
    }
    // cout << "[Error injected...]";
}

Network::Network(const string error_type)
{
    this->sock = INVALID_SOCKET;
    this->error_type = error_type;
}

Network::~Network()
{
    cleanup();
}

bool Network::init()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        cout << "WSAStartup failed: " << result << endl;
        return false;
    }
    return true;
}

bool Network::connectToServer(const Packet &pkt, Mode &mode)
{
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        cout << "Socket creation failed: " << WSAGetLastError() << endl;
        cleanup();
        return false;
    }

    const string ip = pkt.getServerIP();
    const int port = pkt.getServerPort();

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    int result = ::connect(sock, (sockaddr *)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR)
    {
        cout << "Connection failed: " << WSAGetLastError() << endl;
        closesocket(sock);
        sock = INVALID_SOCKET;
        cleanup();
        return false;
    }

    Sleep(2000);
    cout << "Connection established to " << ip << ":" << port << endl;

    // ---- Send handshake control message ----
    string handshake = getStrFromMode(mode);
    int bytesSent = send(sock, handshake.c_str(), handshake.size(), 0);
    if (bytesSent == SOCKET_ERROR)
    {
        cout << "Handshake send failed: " << WSAGetLastError() << endl;
        closesocket(sock);
        sock = INVALID_SOCKET;
        cleanup();
        return false;
    }

    Sleep(1000);
    cout << "Handshake Mode: " << handshake << endl;

    return true;
}

bool Network::sendMessage(const Packet &pkt)
{
    if (sock == INVALID_SOCKET)
    {
        cout << "Socket not connected." << endl;
        return false;
    }

    // SERIALIZE PACKET FOR TRANSFER
    string data = pkt.getData();
    int data_size = data.length();

    string wire = pkt.serialize();

    // Extract payload from packet (payload = data)
    auto sep = wire.find('|');
    if (sep != string::npos)
    {
        string header = wire.substr(0, sep + 1);
        string payload = wire.substr(sep + 1);

        if (!error_type.empty())
        {
            if (error_type != "none")
            {
                injectError(payload);
            }
        }

        wire = header + payload;
    }
    else
    {
        // if no payload found
        if (!error_type.empty())
            injectError(wire);
    }

    int result = send(sock, wire.c_str(), (int)wire.size(), 0);
    if (result == SOCKET_ERROR)
    {
        cout << "Send failed: " << WSAGetLastError() << endl;
        closesocket(sock);
        sock = INVALID_SOCKET;
        cleanup();
        return false;
    }

    if (data_size > 1)
        cout << data_size << " bits";

    return true;
}

void Network::cleanup()
{
    if (sock != INVALID_SOCKET)
    {
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
    WSACleanup();
}