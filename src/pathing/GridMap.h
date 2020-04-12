//
// Created by philip on 1/23/20.
//

#ifndef SOCIETY_GRIDMAP_H
#define SOCIETY_GRIDMAP_H

#include <memory>
#include <vector>
#include <pathing/QuadTree.h>

#include "Map.h"
#include "GridNode.h"


class GridMap : public Map {
public:
    typedef std::shared_ptr<GridMap> Ptr;

    GridMap(int width, int height) : GridMap(0, 0, width, height) {}

    GridMap(int xOffset, int yOffset, int width, int height);

    // topology
    std::vector<MapNode::Ptr> &getNodes() override {
        std::vector<MapNode::Ptr> temp;
        for (const auto &node: nodes)
            temp.push_back(node);
        return temp;
    }

    MapNode::Ptr getNode(int x, int y) override;

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

private:
    const int width;
    const int height;
    std::vector<GridNode::Ptr> nodes;
    QuadTree collisionTreeHead;
};


#endif //SOCIETY_GRIDMAP_H
