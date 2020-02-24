//
// Created by Philip on 2/23/2020.
//

#ifndef HIVEMIND_STRUCTURENODE_H
#define HIVEMIND_STRUCTURENODE_H

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "MapNode.h"
#include "Structure.h"


class StructureNode : public MapNode, public std::enable_shared_from_this<StructureNode> {
public:
    Structure::Ptr structure;

    // Construct from scratch
    StructureNode(int x, int y);
    StructureNode(int x, int y, bool passable);
    StructureNode(int x, int y, int width, int height);
    StructureNode(int x, int y, int width, int height, bool passable);

    // Construct and inject into map
    StructureNode(const MapNode::Ptr &position, bool passable);

    // First node is used as "anchor" node
    explicit StructureNode(std::vector<MapNode::Ptr> nodes);
    StructureNode(std::vector<MapNode::Ptr> nodes, bool passable);

    int width;
    int height;
private:
    bool isNeighbor(const Ptr& node);
};


#endif //HIVEMIND_STRUCTURENODE_H
