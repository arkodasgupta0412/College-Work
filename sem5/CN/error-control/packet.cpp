#include "packet.h"
#include <string>
#include <stdexcept>
using namespace std;

/*

*/

// PACKET CONSTRUCTOR
Packet::Packet(string _data, string _cIP, string _sIP, int _cPort, int _sPort)
{
    data = _data;
    ipHeader.ClientIP = _cIP;
    ipHeader.ServerIP = _sIP;
    tcpHeader.ClientPort = _cPort;
    tcpHeader.ServerPort = _sPort;
}

// PACKET DESTRUCTOR
Packet::~Packet() {}

// SERIALIZATION
string Packet::serialize() const
{
    return ipHeader.ClientIP + ":" + to_string(tcpHeader.ClientPort) +
           "->" + ipHeader.ServerIP + ":" + to_string(tcpHeader.ServerPort) +
           "|" + data;
}

// DESERIALIZATION
Packet Packet::deserialize(const string &deserialized_data)
{
    auto sep1 = deserialized_data.find('-');
    auto sep2 = deserialized_data.find('|');

    if (sep1 == string::npos || sep2 == string::npos)
        throw runtime_error("Invalid packet format");

    // client ip/port
    string client_ip_port = deserialized_data.substr(0, sep1);
    auto sep3 = client_ip_port.find(":");
    if (sep3 == string::npos)
        throw runtime_error("Invalid client header");

    string client_ip = client_ip_port.substr(0, sep3);
    int client_port = stoi(client_ip_port.substr(sep3 + 1));

    // server ip/port
    string dest_ip_port = deserialized_data.substr(sep1 + 2, sep2 - (sep1 + 2));
    auto sep4 = dest_ip_port.find(":");
    if (sep4 == string::npos)
        throw runtime_error("Invalid server header");

    string server_ip = dest_ip_port.substr(0, sep4);
    int server_port = stoi(dest_ip_port.substr(sep4 + 1));

    // payload
    string data = deserialized_data.substr(sep2 + 1);

    return Packet(data, client_ip, server_ip, client_port, server_port);
}