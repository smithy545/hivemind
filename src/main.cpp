#include <iostream>
#include <thread>

#include "thread/GameRunner.h"


int main() {
    std::cout << "Starting main thread." << std::endl;

    std::thread gameThread([] { return GameRunner::loop(); });

    std::cout << "Waiting for main thread " << gameThread.get_id() << " to join..." << std::endl;

    gameThread.join();

    std::cout << "Ending." << std::endl;

    return 0;
}
