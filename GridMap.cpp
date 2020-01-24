//
// Created by philip on 1/23/20.
//

#include "GridMap.h"

GridMap::GridMap(int width, int height)  :  width(width),
                                            height(height) {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            nodes.push_back(MapNode(x, y));
        }
    }
}

std::vector<Map::MapNode> GridMap::getNeighbors(MapNode position) {
    std::vector<MapNode> v;
    return v;
}

std::vector<Map::MapNode> GridMap::getNodes() {
    return nodes;
}

const int &GridMap::Width() const {
    return width;
}

const int &GridMap::Height() const {
    return height;
}