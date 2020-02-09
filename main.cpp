
#include <iostream>

#include "GameRunner.h"


int main() {
    GameRunner gr;

    std::cout << "Starting main thread." << std::endl;

    std::vector<GridMap::Ptr> loadedMaps;

    std::thread main_thread(std::bind(GameRunner::loop, loadedMaps));

    std::cout << "Waiting for main thread " << main_thread.get_id() << " to join..." << std::endl;

    main_thread.join();

    std::cout << "Ending." << std::endl;

    return 0;
}
