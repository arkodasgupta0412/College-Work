#include "client.h"
#include <iostream>
using namespace std;

void showUsage()
{
    cout << "Usage: run_client.exe --dest <ip> <port> "
            "--scheme <crc8|crc10|crc16|crc32|checksum> "
            "--payload <size> --window <size> "
            "--loss <prob> --error <prob> "
            "--input <filename> --mode <SW|GBN|SR>"
         << endl;
}

int main(int argc, char **argv)
{
    string serverIp = "127.0.0.1";
    int serverPort = 5400;
    string mode = "GBN";
    int windowSize = 4, payloadSize = 46, crcType = 32;
    double loss = 0.15, error = 0.15;
    string checksumScheme = "crc32", inputFilename = "input.txt";

    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i];
        if (arg == "--dest" && i + 2 < argc)
        {
            serverIp = argv[++i];
            serverPort = stoi(argv[++i]);
        }
        else if (arg == "--scheme" && i + 1 < argc)
        {
            string scheme = argv[++i];
            if (scheme.find("crc") == 0)
            {
                checksumScheme = "crc";
                crcType = stoi(scheme.substr(3));
            }
            else if (scheme == "checksum")
                checksumScheme = "checksum";
        }
        else if (arg == "--payload")
            payloadSize = stoi(argv[++i]);
        else if (arg == "--window")
            windowSize = stoi(argv[++i]);
        else if (arg == "--loss")
            loss = stod(argv[++i]);
        else if (arg == "--error")
            error = stod(argv[++i]);
        else if (arg == "--input")
            inputFilename = argv[++i];
        else if (arg == "--mode")
            mode = argv[++i];
        else
        {
            showUsage();
            return 1;
        }
    }

    Sender sender(serverIp, serverPort, mode, windowSize, loss, error,
                  400, payloadSize, crcType, checksumScheme, inputFilename);

    sender.processFile();
    sender.printStats(inputFilename);
}
