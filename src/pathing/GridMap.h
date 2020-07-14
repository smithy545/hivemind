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

using std::vector;


class GridMap : public Map {
public:
    POINTERIZE(GridMap);

    class GridNode : public MapNode {
    public:
        POINTERIZE(GridNode);

        GridNode(int x, int y) : GridNode(x, y, true) {};
        GridNode(int x, int y, bool passable) : _x(x), _y(y), _passable(passable) {}

        _VAR_GET(int, x, public);
        _VAR_GET(int, y, public);
        _BVAR_GET(passable, public);
    };

    GridMap(int width, int height);

    GridMap(int xOffset, int yOffset, int width, int height);

    vector<MapNode::Ptr> &get_dirty_nodes() override;

    MapNode::Ptr get_node(int x, int y) override;

    vector<MapNode::Ptr> get_neighbors(MapNode::Ptr node) override;

    _VAR_GET(int, width, public);
    _VAR_GET(int, height, public);
    _REFVAR_GET(vector<MapNode::Ptr>, nodes, public);
private:
    vector<MapNode::Ptr> ret;
};


#endif //SOCIETY_GRIDMAP_H
