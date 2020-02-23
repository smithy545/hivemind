//
// Created by philip on 1/23/20.
//

#include "Human.h"

Human::Human(const MapPosition& initialPosition) : MapActor(initialPosition) {}

void Human::update() {
    if(!path.empty()) {
        // set position to next in path
        position = MapPosition(path.front());
        path.erase(path.begin(), path.begin()+1);
    } else {
        if (role != nullptr) {
            // determine next task from role here
        }
    }
}
