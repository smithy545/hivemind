//
// Created by philip on 1/23/20.
//

#include "Robot.h"


Robot::Robot(Map::MapNode position)
        : position(std::make_shared<Map::MapNode>(position.x, position.y)),
          path() {}

void Robot::update() {
    // set position to next in path
    Map::MapNode nextPos = path.front();
    position = std::make_shared<Map::MapNode>(nextPos.x, nextPos.y);
    path.pop();
}

const std::queue<Map::MapNode> &Robot::Path() const {
    return path;
}

const std::shared_ptr<Map::MapNode> &Robot::Position() const {
    return position;
}
