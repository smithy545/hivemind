//
// Created by smith on 4/12/2020.
//

#include "GridNode.h"

GridNode::GridNode(int x, int y) : GridNode(x, y, true) {}

GridNode::GridNode(int x, int y, bool passable) : x(x), y(y), passable(passable) {}

int GridNode::getX() {
    return x;
}

int GridNode::getY() {
    return y;
}

bool GridNode::isPassable() {
    return passable;
}