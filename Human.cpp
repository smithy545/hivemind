//
// Created by philip on 1/23/20.
//

#include "Human.h"

#include <iostream>
#include <utility>


Human::Human(std::string name) : MapActor(), name(std::move(name)) {}

void Human::update(GridMap::Ptr map) {
    if(!path.empty()) {
        // move and if successful update path
        if(map->moveActor(std::weak_ptr<MapActor>(this->shared_from_this()), path.back())) {
            path.pop_back();
        } else {
            std::cout <<
            "Could not move from (" <<
                position->node->x << ", " << position->node->y
            << ") to (" <<
                path.back()->x << ", " << path.back()->y
            << ")" << std::endl;
        }
    } else if (role != nullptr) {
        // determine next task from role here
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
