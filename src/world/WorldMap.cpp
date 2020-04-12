//
// Created by smith on 4/9/2020.
//

#include "WorldMap.h"

WorldMap::WorldMap() {}


const std::vector<MapNode::Ptr> &WorldMap::getNodes() {
    std::vector<MapNode::Ptr> nodes;
    for (const auto &map: subMaps)
        for (const auto &node: map->getNodes())
            nodes.push_back(node);
    return std::move(nodes);
}

MapNode::Ptr WorldMap::getNode(int x, int y) {
    for (const auto &map: subMaps) {
        auto node = map->getNode(x, y);
        if (node != nullptr)
            return node;
    }
    // TODO: Add check to remove any overlap of new map with existing maps
    auto newMap = std::make_shared<GridMap>(x - 50, y - 50, 100, 100);
    return newMap->getNode(x, y);
}

void WorldMap::addPerson() {}

void WorldMap::expandNorth() {}
void WorldMap::expandWest() {}
void WorldMap::expandSouth() {}
void WorldMap::expandEast() {}
