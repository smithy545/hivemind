//
// Created by philip on 1/23/20.
//

#include "Human.h"

void Human::update() {
    // set position to next in path
    position = MapPosition(path.front());
    path.erase(path.begin(), path.begin()+1);
}
