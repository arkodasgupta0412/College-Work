#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    std::cout << "Sleeping...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Awake!\n";
    return 0;
}