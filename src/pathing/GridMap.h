//
// Created by philip on 1/23/20.
//

#ifndef SOCIETY_GRIDMAP_H
#define SOCIETY_GRIDMAP_H

#include <vector>

#include "collision/QuadTree.h"
#include "macros.h"
#include "Map.h"
#include "MapNode.h"


class GridMap : public Map {
public:
    POINTERIZE(GridMap);

    class GridNode : public MapNode {
    public:
        POINTERIZE(GridNode);

        GridNode(int x, int y) : GridNode(x, y, true) {};

        GridNode(int x, int y, bool passable) : _x(x), _y(y), _passable(passable) {}

        _VAR_GETSET(x, int, public, private)
        _VAR_GETSET(y, int, public, private)
        _BVAR_GETSET(passable, public, private)
    };

    GridMap(int width, int height);

    GridMap(int xOffset, int yOffset, int width, int height);

    MapNode::Ptr get_node(int x, int y) override;

    std::vector<MapNode::Ptr> get_neighbors(MapNode::Ptr node) override;

    _VAR_GETSET(width, int, public, private)
    _VAR_GETSET(height, int, public, private)
    _REFVAR_GET(nodes, std::vector<MapNode::Ptr>, public)
};


#endif //SOCIETY_GRIDMAP_H
