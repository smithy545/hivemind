//
// Created by Philip on 3/29/2020.
//

#include "MapNode.h"


MapNode::MapNode(int x, int y) : MapNode(x, y, true) {}

MapNode::MapNode(int x, int y, bool passable) : MapNode(x, y, passable, GROUND) {}

MapNode::MapNode(int x, int y, bool passable, Type type) : x(x), y(y), passable(passable), type(type) {}

int MapNode::getX() const {
    return x;
}

void MapNode::setX(int x) {
    this->x = x;
}

int MapNode::getY() const {
    return y;
}

void MapNode::setY(int y) {
    this->y = y;
}

bool MapNode::isPassable() const {
    return passable;
}

void MapNode::setPassable(bool val) {
    passable = val;
}

std::unordered_set<MapNode::Ptr> &MapNode::getNeighbors() {
    return neighbors;
}

MapNode::Type MapNode::getType() const {
    return type;
}

void MapNode::setType(Type type) {
    MapNode::type = type;
}