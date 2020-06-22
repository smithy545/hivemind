//
// Created by philip on 1/26/20.
//

#ifndef SOCIETY_MAP_H
#define SOCIETY_MAP_H

#include <vector>

#include "macros.h"
#include "MapNode.h"


class Map {
public:
    POINTERIZE(Map);

    virtual const std::vector<MapNode::Ptr> &get_nodes() = 0;

    // nullptr return value means position out of bounds
    virtual MapNode::Ptr get_node(int x, int y) = 0;

    virtual std::vector<MapNode::Ptr> get_neighbors(MapNode::Ptr node) = 0;

    // Force bound checking in getNode!
    bool inBounds(int x, int y) {
        return get_node(x, y) != nullptr;
    }
protected:
    Map() : Map(0, 0) {}

    Map(int xOffset, int yOffset) : _x_offset(xOffset), _y_offset(yOffset) {}

    _VAR(int,x_offset,protected,protected,)
    _VAR(int,y_offset,protected,protected,)
};

#endif //SOCIETY_MAP_H
