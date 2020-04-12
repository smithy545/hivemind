//
// Created by Philip on 3/29/2020.
//

#include "GridNode.h"


GridNode::GridNode(int x, int y) : GridNode(x, y, true) {}

GridNode::GridNode(int x, int y, bool passable) : GridNode(x, y, passable, 0) {}

GridNode::GridNode(int x, int y, bool passable, int type) : x(x), y(y), passable(passable), type(type) {}

int GridNode::getX() {
    return x;
}

void GridNode::setX(int x) {
    this->x = x;
}

int GridNode::getY() {
    return y;
}

void GridNode::setY(int y) {
    this->y = y;
}

bool GridNode::isPassable() {
    return passable;
}

void GridNode::setPassable(bool val) {
    passable = val;
}

std::unordered_set<MapNode::Ptr> &GridNode::getNeighbors() {
    std::unordered_set<MapNode::Ptr> nodes;
    for (const auto &node: neighbors)
        nodes.insert(node);
    return nodes;
}

int GridNode::getType() const {
    return type;
}

void GridNode::setType(int type) {
    this->type = type;
}
