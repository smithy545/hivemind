//
// Created by Philip on 5/18/2020.
//

#ifndef SOCIETY_TOPOLOGICALMAP_H
#define SOCIETY_TOPOLOGICALMAP_H

#include <vector>

#include "macros.h"
#include "Map.h"
#include "MapNode.h"


// Map where global structure is defined by local connections between nodes (local neighbor structure)
class TopologicalMap : public Map {
public:
    POINTERIZE(TopologicalMap);

    TopologicalMap();

    const std::vector<MapNode::Ptr> &getNodes() override;

    MapNode::Ptr getNode(int x, int y) override;

    std::vector<MapNode::Ptr> getNeighbors(MapNode::Ptr node) override;
};


#endif //SOCIETY_TOPOLOGICALMAP_H
