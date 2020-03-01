//
// Created by philip on 1/26/20.
//

#ifndef HIVEMIND_MAP_H
#define HIVEMIND_MAP_H

#include <iterator>
#include <memory>
#include <vector>
#include <vector>

#include "src/world/MapActor.h"
#include "MapNode.h"
#include "src/render/Mesh.h"


class Map {
public:
    typedef std::shared_ptr<Map> Ptr;

    // topology
    virtual const std::vector<MapNode::Ptr> &getNodes() = 0;
    virtual MapNode::Ptr getNode(int x, int y) = 0;
};

#endif //HIVEMIND_MAP_H
