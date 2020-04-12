//
// Created by smith on 4/9/2020.
//

#include "GridMap.h"


GridMap::GridMap(int xOffset, int yOffset, int width, int height) : Map(xOffset, yOffset), width(width),
                                                                    height(height) {
    // initialize
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            nodes.push_back(std::make_shared<MapNode>(xOffset + x, yOffset + y));
        }
    }
    // setup topology
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * width + x;
            MapNode::Ptr node = nodes[index];
            const bool xgt0 = x > 0;
            const bool ygt0 = y > 0;
            const bool xltw = x < width - 1;
            const bool ylth = y < height - 1;
            if (xgt0)
                node->getNeighbors().insert(nodes[index - 1]);
            if (xltw)
                node->getNeighbors().insert(nodes[index + 1]);
            if (ygt0)
                node->getNeighbors().insert(nodes[index - width]);
            if (ylth)
                node->getNeighbors().insert(nodes[index + width]);
            if (xgt0 && ygt0)
                node->getNeighbors().insert(nodes[index - width - 1]);
            if (xltw && ylth)
                node->getNeighbors().insert(nodes[index + width + 1]);
            if (xgt0 && ylth)
                node->getNeighbors().insert(nodes[index + width - 1]);
            if (xltw && ygt0)
                node->getNeighbors().insert(nodes[index - width + 1]);
        }
    }
}

MapNode::Ptr GridMap::getNode(int x, int y) {
    y -= getYOffset();
    x -= getXOffset();
    unsigned int index = y * width + x;
    if (x >= width || y >= height || x < 0 || y < 0)
        return nullptr;
    return nodes[index];
}
