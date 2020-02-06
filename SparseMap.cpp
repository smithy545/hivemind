//
// Created by philip on 1/26/20.
//

#include "SparseMap.h"

#include <fmt/format.h>


std::vector<MapNode::Ptr> SparseMap::getNodes() {
    std::vector<MapNode::Ptr> all_nodes;
    for(auto itr = nodes.begin(); itr != nodes.end(); itr++) {
        all_nodes.push_back(itr->second);
    }
    return all_nodes;
}

MapNode::Ptr SparseMap::getNode(int x, int y) {
    std::string key = generateKey(x, y);
    if(nodes.count(key) == 0) {
        nodes[key] = std::make_shared<MapNode>(x, y);
    }
    return nodes[key];
}

std::string SparseMap::generateKey(int x, int y) {
    return fmt::format("{}:{}", x, y);
}
