//
// Created by philip on 1/23/20.
//

#include "Human.h"

#include <iostream>
#include <utility>

#include "Pather.h"


Human::Human(std::string name) : MapActor(), name(std::move(name)) {}

void Human::update(GridMap::Ptr map) {
    if(!path.empty()) {
        // move and if successful update path
        if (map->moveEntity(std::weak_ptr<MapEntity>(this->shared_from_this()), path.back())) {
            path.pop_back();
        } else {
            std::cout <<
                      "Could not move from (" <<
                      position->getNode()->getX() << ", " << position->getNode()->getY()
                      << ") to (" <<
                      path.back()->getX() << ", " << path.back()->getY()
                      << ")" << std::endl;
        }
    } else if (role != nullptr) {
        // do current task

        // determine next task from role here
        currentTask = role->getNextTask(currentTask);
        MapNode::Ptr nextPos = role->getTaskDestination(currentTask);

        // path to next task if necessary
        if (nextPos != this->getPosition()->getNode())
            path = Pather::genAStarPath(position->getNode(), nextPos);
    } else {
        // default behaviour here
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

const BaseRole::Ptr &Human::getRole() const {
    return role;
}

const std::string &Human::getCurrentTask() const {
    return currentTask;
}

void Human::setName(const std::string &name) {
    this->name = name;
}

void Human::setVisionMap(const VisionMap::Ptr &visionMap) {
    this->visionMap = visionMap;
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
