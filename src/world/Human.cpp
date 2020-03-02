//
// Created by philip on 1/23/20.
//

#include "Human.h"

#include <iostream>

#include "src/pathing/Pather.h"


Human::Human(std::string name) : WorldActor(), name(std::move(name)) {
    std::cout << "Hi, I'm " << getName() << " and my id is " << getId() << std::endl;
}

WorldActor::Action Human::update(GridMap::Ptr map) {
    if (!path.empty()) {
        // move and if successful update path
        if (map->moveEntity(this->shared_from_this(), path.back())) {
            path.pop_back();
            return MOVE;
        } else {
            std::cout <<
                      "Could not move from (" <<
                      position->getX() << ", " << position->getY()
                      << ") to (" <<
                      path.back()->getX() << ", " << path.back()->getY()
                      << ")" << std::endl;
            path.clear();
        }
    } else if (role != nullptr) {
        // do current task

        // determine next task from role here
        currentTask = role->getNextTask(currentTask);
        MapNode::Ptr nextPos = role->getTaskDestination(currentTask);

        // path to next task if necessary
        if (nextPos != this->getPosition())
            path = Pather::genAStarPath(position, nextPos);
    }
    // default behaviour
    return IDLE;
}

const std::string &Human::getName() const {
    return name;
}

const std::unordered_map<std::string, Human::Relationship::Ptr> &Human::getRelationships() const {
    return relationships;
}

const BaseRole::Ptr &Human::getRole() const {
    return role;
}

const std::string &Human::getCurrentTask() const {
    return currentTask;
}

void Human::setName(const std::string &name) {
    this->name = name;
}

void Human::setRelationships(const std::unordered_map<std::string, Relationship::Ptr> &relationships) {
    this->relationships = relationships;
}

void Human::setRole(const BaseRole::Ptr &role) {
    this->role = role;
}

void Human::setCurrentTask(const std::string &currentTask) {
    this->currentTask = currentTask;
}
