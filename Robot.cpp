//
// Created by philip on 1/23/20.
//

#include "Robot.h"


Robot::Robot(MapNode position)
        : position(std::make_shared<MapNode>(position.x, position.y)),
          path() {}

void Robot::update() {
    // set position to next in path
    MapNode nextPos = path.front();
    position = std::make_shared<MapNode>(nextPos.x, nextPos.y);
    path.pop();
}

const std::queue<MapNode> &Robot::Path() const {
    return path;
}

const MapNode::Ptr &Robot::Position() const {
    return position;
}
