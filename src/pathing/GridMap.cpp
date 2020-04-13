//
// Created by smith on 4/9/2020.
//

#include "GridMap.h"
#include "GridNode.h"


GridMap::GridMap(int xOffset, int yOffset, int width, int height) : Map(xOffset, yOffset),
                                                                    width(width),
                                                                    height(height),
                                                                    collisionTreeHead(0, Rectangle(width, height)) {
    // initialize
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            nodes.push_back(std::make_shared<GridNode>(xOffset + x, yOffset + y));
        }
    }
}

const std::vector<MapNode::Ptr> &GridMap::getNodes() {
    return nodes;
}

MapNode::Ptr GridMap::getNode(int x, int y) {
    y -= getYOffset();
    x -= getXOffset();
    if (x < 0 || y < 0 || x >= width || y >= height)
        return nullptr;
    return nodes[x + y * width];
}

std::vector<MapNode::Ptr> GridMap::getNeighbors(MapNode::Ptr node) {
    std::vector<MapNode::Ptr> neighbors;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int x = node->getX() + dx;
            int y = node->getY() + dy;
            auto neighbor = getNode(x, y);
            if (neighbor != nullptr && x != node->getX() && y != node->getY())
                neighbors.push_back(getNode(x, y));
        }
    }
    return neighbors;
}

int GridMap::getWidth() {
    return width;
}

int GridMap::getHeight() {
    return height;
}
