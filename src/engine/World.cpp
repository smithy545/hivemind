//
// Created by smith on 4/9/2020.
//

#include "World.h"

#include <iostream>


World::World() : World(0, 0) {}

World::World(int xOffset, int yOffset) : Map(xOffset, yOffset) {
    subMaps[0][0] = std::make_shared<GridMap>(xOffset, yOffset, subMapSize, subMapSize);
    width = subMapSize;
    height = subMapSize;
}

const std::vector<MapNode::Ptr> &World::getNodes() {
    std::vector<MapNode::Ptr> nodes;
    int sw = width / subMapSize;
    int sh = height / subMapSize;
    for (int sy = 0; sy < sw; sy++) {
        for (int sx = 0; sx < sh; sx++) {
            auto map = subMaps[sy][sx];

            for (const auto &node: map->getNodes())
                nodes.push_back(node);
        }
    }
    return std::move(nodes);
}

MapNode::Ptr World::getNode(int x, int y) {
    if (x >= getXOffset() + MAX_SUBMAP_X * subMapSize || x < getXOffset() ||
        y >= getYOffset() + MAX_SUBMAP_Y * subMapSize || y < getYOffset()) {
        std::cerr << "Cannot get node at (" << x << ", " << y << "): Out of range";
        return nullptr;
    }

    int sx = x / subMapSize;
    int sy = y / subMapSize;

    if (x >= width) {
        subMaps[width / subMapSize][sy] = std::make_shared<GridMap>(x, y, subMapSize, subMapSize);
        width += subMapSize;
    }
    if (y >= height) {
        subMaps[sx][height / subMapSize] = std::make_shared<GridMap>(x, y, subMapSize, subMapSize);
        height += subMapSize;
    }

    return subMaps[sy][sx]->getNode(x, y);
}

std::vector<MapNode::Ptr> World::getNeighbors(MapNode::Ptr node) {
    int neighborMatrix[8][2] = {
            {-1, -1},
            {0,  -1},
            {1,  -1},
            {-1, 0},
            {1,  0},
            {-1, 1},
            {0,  1},
            {1,  1},
    };
    int nx = node->getX();
    int ny = node->getY();
    std::vector<MapNode::Ptr> neighbors;

    for (auto pos: neighborMatrix) {
        auto neighbor = getNode(nx + pos[0], ny + pos[1]);
        if (neighbor != nullptr)
            neighbors.push_back(neighbor);
    }

    return neighbors;
}
