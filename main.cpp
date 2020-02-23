
#include <iostream>
#include <memory>
#include "GameRunner.h"


int main() {
    std::cout << "Starting main thread." << std::endl;

    std::thread main_thread([] { return GameRunner::loop(); });

    std::cout << "Waiting for main thread " << main_thread.get_id() << " to join..." << std::endl;

    main_thread.join();

    std::cout << "Ending." << std::endl;

    return 0;
}
