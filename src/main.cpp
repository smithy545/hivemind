#include <iostream>
#include <thread>

#include "GameRunner.h"


int main() {
    std::cout << "Begin Society" << std::endl;
    std::thread gameThread(GameRunner::loop);
    gameThread.join();
    std::cout << "End." << std::endl;

    return 0;
}
