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

        _VAR(int,x,public,private,)
        _VAR(int,y,public,private,)

        bool isPassable() override {
            return _passable;
        }
    private:
        bool _passable;
    };

    GridMap(int width, int height);

    GridMap(int xOffset, int yOffset, int width, int height);

    const std::vector<MapNode::Ptr> &get_nodes() override;

    MapNode::Ptr get_node(int x, int y) override;

    std::vector<MapNode::Ptr> get_neighbors(MapNode::Ptr node) override;
private:
    _VAR(int,width,public,private,)
    _VAR(int,height,public,private,)
    std::vector<MapNode::Ptr> nodes;
    QuadTree collisionTreeHead;
};


#endif //SOCIETY_GRIDMAP_H
