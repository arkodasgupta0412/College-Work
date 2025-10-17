#include "server.h"
#include <iostream>
#include <string>

using namespace std;

void showUsage()
{
    cout << "Usage: run_server.exe "
         << "--port <port> "
         << "--mode <SW|GBN|SR> "
         << "--scheme <checksum|crc8|crc10|crc16|crc32> "
         << "[--window <size>]" << endl;
    cout << "Note: Window size ignored for SW and GBN" << endl;
}

int main(int argc, char *argv[])
{
    int port = 8080;
    string mode = "SW";      // default
    string scheme = "crc32"; // default
    int windowSize = 4;      // default for SR

    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i];

        if (arg == "--port" && i + 1 < argc)
        {
            port = stoi(argv[++i]);
        }
        else if (arg == "--mode" && i + 1 < argc)
        {
            mode = argv[++i];
            if (mode != "SW" && mode != "GBN" && mode != "SR")
            {
                cerr << "Invalid mode. Use SW, GBN, or SR" << endl;
                return 1;
            }
        }
        else if (arg == "--scheme" && i + 1 < argc)
        {
            scheme = argv[++i];
            if (scheme != "checksum" &&
                scheme != "crc8" && scheme != "crc10" &&
                scheme != "crc16" && scheme != "crc32")
            {
                cerr << "Invalid scheme. Use checksum, crc8, crc10, crc16, or crc32" << endl;
                return 1;
            }
        }
        else if (arg == "--window" && i + 1 < argc)
        {
            windowSize = stoi(argv[++i]);
        }
        else
        {
            showUsage();
            return 1;
        }
    }

    // Force window size to 1 for SW and GBN
    if (mode == "SW" || mode == "GBN")
    {
        windowSize = 1;
    }

    Receiver receiver(port, mode, scheme, windowSize);
    receiver.Run();

    return 0;
}
