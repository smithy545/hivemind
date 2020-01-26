//
// Created by philip on 1/23/20.
//

#include "Human.h"


Human::Human(const MapNode& position)
        : position(std::make_shared<MapNode>(position.x, position.y)),
          path() {}

void Human::update() {
    // set position to next in path
    MapNode nextPos = path.front();
    position = std::make_shared<MapNode>(nextPos.x, nextPos.y);
    path.pop();
}

const std::queue<MapNode> &Human::Path() const {
    return path;
}

const MapNode::Ptr &Human::Position() const {
    return position;
}
