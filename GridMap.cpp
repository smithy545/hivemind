//
// Created by philip on 1/23/20.
//

#include "GridMap.h"

GridMap::GridMap(int width, int height)  :  width(width),
                                            height(height) {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            nodes.push_back(std::make_shared<MapNode>(x, y));
        }
    }
}

std::vector<Map::MapNode::Ptr> GridMap::getNeighbors(MapNode::Ptr position) {
    std::vector<MapNode::Ptr> neighbors;
    const bool xgt0 = position->x > 0;
    const bool ygt0 = position->y > 0;
    const bool xltw = position->x < width;
    const bool ylth = position->y < height;
    if(xgt0)
        neighbors.push_back(nodes[position->y*width + position->x - 1]);
    if(ygt0)
        neighbors.push_back(nodes[(position->y-1)*width + position->x]);
    if(xltw)
        neighbors.push_back(nodes[position->y*width + position->x + 1]);
    if(ylth)
        neighbors.push_back(nodes[(position->y+1)*width + position->x]);
    if(xgt0 && ygt0)
        neighbors.push_back(nodes[(position->y-1)*width + position->x - 1]);
    if(xgt0 && ylth)
        neighbors.push_back(nodes[(position->y+1)*width + position->x - 1]);
    if(xltw && ygt0)
        neighbors.push_back(nodes[(position->y-1)*width + position->x + 1]);
    if(xltw && ylth)
        neighbors.push_back(nodes[(position->y+1)*width + position->x + 1]);

    return neighbors;
}

std::vector<Map::MapNode::Ptr> GridMap::getNodes() {
    return nodes;
}

const int &GridMap::Width() const {
    return width;
}

const int &GridMap::Height() const {
    return height;
}