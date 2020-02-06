//
// Created by philip on 1/26/20.
//

#ifndef HIVEMIND_SPARSEMAP_H
#define HIVEMIND_SPARSEMAP_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Map.h"


class SparseMap : public Map {
public:
    typedef std::shared_ptr<SparseMap> Ptr;

    std::vector<MapNode::Ptr> getNodes() override;
    MapNode::Ptr getNode(int x, int y) override;
private:
    std::unordered_map<std::string, MapNode::Ptr> nodes;

    std::string generateKey(int x, int y);
};


#endif //HIVEMIND_SPARSEMAP_H
