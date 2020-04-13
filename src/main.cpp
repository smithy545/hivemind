#include <iostream>
#include <thread>

#include "thread/GameRunner.h"


int main() {
    std::thread gameThread([] {
        std::cout << "Starting main thread." << std::endl;
        return GameRunner::loop();
    });
    gameThread.join();

    std::cout << "End." << std::endl;

    return 0;
}
