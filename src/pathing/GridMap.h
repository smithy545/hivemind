//
// Created by philip on 1/23/20.
//

#ifndef SOCIETY_GRIDMAP_H
#define SOCIETY_GRIDMAP_H

#include <memory>
#include <vector>

#include "collision/QuadTree.h"
#include "Map.h"
#include "MapNode.h"


class GridMap : public Map {
public:
    typedef std::shared_ptr<GridMap> Ptr;

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
