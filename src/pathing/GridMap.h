//
// Created by philip on 1/23/20.
//

#ifndef SOCIETY_GRIDMAP_H
#define SOCIETY_GRIDMAP_H

#include <memory>
#include <vector>

#include "Map.h"
#include "MapNode.h"


class GridMap : public Map {
public:
    typedef std::shared_ptr<GridMap> Ptr;

    GridMap(int width, int height) : GridMap(0, 0, width, height) {}

    GridMap(int xOffset, int yOffset, int width, int height);

    // topology
    std::vector<MapNode::Ptr> &getNodes() override {
        return nodes;
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
    std::vector<MapNode::Ptr> nodes;
};


#endif //SOCIETY_GRIDMAP_H
