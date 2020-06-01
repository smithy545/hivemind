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

        GridNode(int x, int y, bool passable) : x(x), y(y), passable(passable) {}

        int getX() override {
            return x;
        }

        int getY() override {
            return y;
        }

        bool isPassable() override {
            return passable;
        }
    private:
        int x, y;
        bool passable;
    };

    GridMap(int width, int height);

    GridMap(int xOffset, int yOffset, int width, int height);

    const std::vector<MapNode::Ptr> &getNodes() override;

    MapNode::Ptr getNode(int x, int y) override;

    std::vector<MapNode::Ptr> getNeighbors(MapNode::Ptr node) override;

    int getWidth();

    int getHeight();

private:
    const int width;
    const int height;
    std::vector<MapNode::Ptr> nodes;
    QuadTree collisionTreeHead;
};


#endif //SOCIETY_GRIDMAP_H
