//
// Created by philip on 1/23/20.
//

#include "Human.h"

#include <iostream>
#include <utility>

#include "MapEntity.h"


Human::Human(std::string name) : MapActor(), name(std::move(name)) {}

void Human::update() {
    if(!path.empty()) {
        path.front()->entities[getUId()] = std::shared_ptr<Human>(this);
        position->node->entities.erase(getUId());

        // set node to next in path
        position = std::make_shared<MapPosition>(path.front());
        path.erase(path.begin(), path.begin()+1);
    } else {
        if (role != nullptr) {
            // determine next task from role here
        }
    }
}

const std::string &Human::getName() const {
    return name;
}

const VisionMap::Ptr &Human::getVisionMap() const {
    return visionMap;
}

const std::unordered_map<std::string, Human::Relationship::Ptr> &Human::getRelationships() const {
    return relationships;
}

const BaseRole::Ptr & Human::getRole() const {
    return role;
}

const std::string &Human::getCurrentTask() const {
    return currentTask;
}
