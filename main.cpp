
#include <iostream>
#include <memory>

#include "GameRunner.h"


int main() {
    std::cout << "Starting main thread." << std::endl;

    std::vector<GridMap::Ptr> loadedMaps;

    std::cout << "Loading first map..." << std::endl;
    loadedMaps.push_back(std::make_shared<GridMap>(799, 599));
    std::cout << "Map loaded." << std::endl;

    std::thread main_thread(std::bind(GameRunner::loop, loadedMaps));

    std::cout << "Waiting for main thread " << main_thread.get_id() << " to join..." << std::endl;

    main_thread.join();

    std::cout << "Ending." << std::endl;

    return 0;
}
