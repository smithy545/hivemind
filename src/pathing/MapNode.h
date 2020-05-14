//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_MAPNODE_H
#define SOCIETY_MAPNODE_H

#include <deque>
#include <memory>
#include <unordered_set>

#include "common/TopologicalNode.h"


class MapNode {
public:
    typedef std::shared_ptr<MapNode> Ptr;
    typedef std::deque<Ptr> MapPath;

    virtual int getX() = 0;

    virtual int getY() = 0;

    virtual bool isPassable() = 0;
};

// MapNode containing local neighbor information
class TopologicalMapNode : public MapNode, public TopologicalNode {
public:
    typedef std::shared_ptr<TopologicalMapNode> Ptr;
};

#endif //SOCIETY_MAPNODE_H
