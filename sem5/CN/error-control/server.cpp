#include "server.h"
#include "utils.h"
#include "packet.h"
#include "crc.h"
#include "checksum.h"
#include <iostream>
#include <vector>
using namespace std;

const string clientIP = "127.0.0.1";
const int clientPort = 8000;
const string serverIP = "127.0.0.1";
const int serverPort = 8080;

Server::Server(const string &ip, int port)
{
    this->ip = ip;
    this->port = port;
    this->serverSock = INVALID_SOCKET;
    this->clientSock = INVALID_SOCKET;
}

Server::~Server()
{
    cleanup();
}

bool Server::init()
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

bool Server::start()
{
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == INVALID_SOCKET)
    {
        cout << "Socket creation failed: " << WSAGetLastError() << endl;
        cleanup();
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (bind(serverSock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "Bind failed: " << WSAGetLastError() << endl;
        cleanup();
        return false;
    }

    if (listen(serverSock, 1) == SOCKET_ERROR)
    {
        cout << "Listen failed: " << WSAGetLastError() << endl;
        cleanup();
        return false;
    }

    cout << "[Server] Listening on " << ip << ":" << port << endl;
    return true;
}

bool Server::acceptClient()
{
    sockaddr_in clientAddr{};
    int clientAddrSize = sizeof(clientAddr);
    clientSock = accept(serverSock, (sockaddr *)&clientAddr, &clientAddrSize);

    if (clientSock == INVALID_SOCKET)
    {
        cout << "Accept failed: " << WSAGetLastError() << endl;
        return false;
    }

    cout << "[Server] Client connected." << endl;
    return true;
}

bool Server::receiveHandshake()
{
    char buffer[1024] = {0};
    int bytesReceived = recv(clientSock, buffer, sizeof(buffer), 0);

    if (bytesReceived <= 0)
    {
        cout << "[Server] Handshake receive failed." << endl;
        return false;
    }

    std::string received(buffer, bytesReceived);
    // server accepts Handshaking Mode, sets itself with this mode
    this->mode = getModeFromStr(received);

    if (mode == Mode::UNKNOWN)
    {
        cout << "[Server] Invalid handshake mode received: " << received << endl;
        return false;
    }

    cout << "[Server] Handshake Mode: " << received << endl;
    return true;
}

bool Server::receivePacket(string &serialized_data)
{
    char buffer[2048] = {0};
    int bytesReceived = recv(clientSock, buffer, sizeof(buffer), 0);

    if (bytesReceived <= 0)
        return false;

    string rawData(buffer, bytesReceived);
    serialized_data = rawData;

    Packet pkt = Packet::deserialize(rawData);

    // Check if destination matches the server
    if (pkt.getServerIP() != ip || pkt.getServerPort() != port)
    {
        cout << "[Server] Packet dropped (invalid destination)." << endl;
        return false;
    }

    if (pkt.getData().length() > 3)
        cout << "\n[Server] Packet received: " << pkt.getData() << endl;

    return true;
}

void Server::processPacket(const Packet &pkt)
{
    string data = pkt.getData();
    bool encode = false;

    if (mode == Mode::CRC8)
    {
        cout << "[Server] Checking CRC8...\n";
        if (CRC(data, 8, encode) != string(8, '0'))
            cout << "[Server] ERROR detected! Packet dropped\n";
        else
            cout << "[Server] Packet valid. Accepted\n";
    }

    else if (mode == Mode::CRC10)
    {
        cout << "[Server] Checking CRC10...\n";
        if (CRC(data, 10, encode) != string(10, '0'))
            cout << "[Server] ERROR detected! Packet dropped\n";
        else
            cout << "[Server] Packet valid. Accepted\n";
    }

    else if (mode == Mode::CRC16)
    {
        cout << "[Server] Checking CRC16...\n";
        if (CRC(data, 16, encode) != string(16, '0'))
            cout << "[Server] ERROR detected! Packet dropped\n";
        else
            cout << "[Server] Packet valid. Accepted\n";
    }

    else if (mode == Mode::CRC32)
    {
        cout << "[Server] Checking CRC32...\n";
        if (CRC(data, 32, encode) != string(32, '0'))
            cout << "[Server] ERROR detected! Packet dropped\n";
        else
            cout << "[Server] Packet valid. Accepted\n";
    }

    else if (mode == Mode::CHECKSUM)
    {
        static vector<string> checksumPackets;
        static int frameSize = 0;

        // First packet -> to get frame Size
        if (frameSize == 0)
            frameSize = data.size();

        // Fetch packets until END marker reached
        if (data.length() > 1)
        {
            // store without processing
            checksumPackets.push_back(data);
            return;
        }

        // If END received -> validate checksum
        cout << "[Server] All packets received. Checking checksum...\n";
        Sleep(1500);

        // Compute checksum (including last data)
        string checksum = Checksum(checksumPackets, frameSize);

        if (checksum == string(frameSize, '0'))
            cout << "[Server] Packets valid. Packets Accepted\n";
        else
            cout << "[Server] ERROR detected. Packets Dropped\n";

        // Reset for next transmission
        checksumPackets.clear();
        frameSize = 0;
    }

    else
    {
        cout << "[Server] Unknown error detection mode.\n";
    }
}

void Server::cleanup()
{
    if (clientSock != INVALID_SOCKET)
    {
        closesocket(clientSock);
        clientSock = INVALID_SOCKET;
    }

    if (serverSock != INVALID_SOCKET)
    {
        closesocket(serverSock);
        serverSock = INVALID_SOCKET;
    }

    WSACleanup();
}

int main()
{
    Server server(serverIP, serverPort);

    if (!server.init())
        return -1;

    if (!server.start())
        return -1;

    if (!server.acceptClient())
        return -1;

    if (!server.receiveHandshake())
        return -1;

    // continuously receive packets
    while (true)
    {
        string serialized;
        if (!server.receivePacket(serialized))
        {
            // cout << "[Server] Packet dropped\n";
            break;
        }

        Packet pkt = Packet::deserialize(serialized);
        server.processPacket(pkt);
    }

    server.cleanup();

    Sleep(700);
    cout << "\n[Server] CONNECTION CLOSED\n";

    return 0;
}