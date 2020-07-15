//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_MAPNODE_H
#define SOCIETY_MAPNODE_H

#include <deque>
#include <unordered_set>

#include "common/TopologicalNode.h"
#include "macros.h"


class MapNode {
public:
    PTR(MapNode);
    typedef std::deque<Ptr> MapPath;

    virtual int get_x() const = 0;

    virtual int get_y() const = 0;

    virtual bool is_passable() const = 0;

    BVAR(dirty, public, public){false};
};

// MapNode containing local neighbor information
class TopologicalMapNode : public MapNode, public TopologicalNode {
public:
    PTR(TopologicalMapNode);
};

#endif //SOCIETY_MAPNODE_H
