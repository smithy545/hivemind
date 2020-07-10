//
// Created by philip on 1/26/20.
//

#ifndef SOCIETY_MAP_H
#define SOCIETY_MAP_H

#include <vector>

#include "macros.h"
#include "MapNode.h"

using std::vector;


class Map {
public:
    POINTERIZE(Map);

    virtual vector<MapNode::Ptr> &get_nodes() = 0;

    // get nodes changed since last check
    virtual vector<MapNode::Ptr> &get_dirty_nodes() = 0;

    // nullptr return value means position out of bounds
    virtual MapNode::Ptr get_node(int x, int y) = 0;

    virtual vector<MapNode::Ptr> get_neighbors(MapNode::Ptr node) = 0;

    // Force bound checking in getNode!
    bool in_bounds(int x, int y) {
        return get_node(x, y) != nullptr;
    }
protected:
    Map() : Map(0, 0) {}

    Map(int x_offset, int y_offset) : _x_offset(x_offset), _y_offset(y_offset) {}

    _VAR_GETSET(int, x_offset, protected, protected);
    _VAR_GETSET(int, y_offset, protected, protected);
};

#endif //SOCIETY_MAP_H
