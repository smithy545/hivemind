//
// Created by philip on 1/26/20.
//

#ifndef HIVEMIND_SPARSEMAP_H
#define HIVEMIND_SPARSEMAP_H

#include <memory>

#include "Map.h"

class SparseMap : public Map {
public:
    typedef std::shared_ptr<SparseMap> Ptr;
    
    std::vector<MapNode::Ptr> getNodes() override;
    MapNode::Ptr getNode(int x, int y) override;
private:
    std::vector<MapNode::Ptr> nodes;
};


#endif //HIVEMIND_SPARSEMAP_H
