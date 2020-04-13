//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_TOPOLOGICALNODE_H
#define SOCIETY_TOPOLOGICALNODE_H

#include <memory>
#include <vector>

#include "MapNode.h"


class TopologicalNode : public MapNode {
public:
    typedef std::shared_ptr<TopologicalNode> Ptr;

    virtual std::vector<MapNode::Ptr> &getNeighbors() = 0;
};

#endif //SOCIETY_TOPOLOGICALNODE_H
