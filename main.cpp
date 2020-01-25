
#include "GameRunner.h"

#include <iostream>

int main() {
    GameRunner gr;

    std::cout << "Starting main thread." << std::endl;

    std::thread main(GameRunner::loop);

    std::cout << "Waiting for main thread to join..." << std::endl;

    main.join();

    std::cout << "Ending." << std::endl;

    return 0;
}
