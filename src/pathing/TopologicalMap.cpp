//
// Created by Philip on 5/18/2020.
//

#include "TopologicalMap.h"


TopologicalMap::TopologicalMap() = default;

const std::vector<MapNode::Ptr> &TopologicalMap::getNodes() {
    std::vector<MapNode::Ptr> nodes;
    return std::move(nodes);
}

MapNode::Ptr TopologicalMap::getNode(int x, int y) {
    return nullptr;
}

std::vector<MapNode::Ptr> TopologicalMap::getNeighbors(MapNode::Ptr node) {
    return std::vector<MapNode::Ptr>();
}

