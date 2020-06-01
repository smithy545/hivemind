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
    POINTERIZE(Map)

    virtual const std::vector<MapNode::Ptr> &getNodes() = 0;

    // nullptr return value means position out of bounds
    virtual MapNode::Ptr getNode(int x, int y) = 0;

    virtual std::vector<MapNode::Ptr> getNeighbors(MapNode::Ptr node) = 0;

    // Force bound checking in getNode!
    bool inBounds(int x, int y) {
        return getNode(x, y) != nullptr;
    }
protected:
    Map() : Map(0, 0) {}

    Map(int xOffset, int yOffset) : xOffset(xOffset), yOffset(yOffset) {}

    int getXOffset() const {
        return xOffset;
    }

    void setXOffset(int xOffset) {
        Map::xOffset = xOffset;
    }

    int getYOffset() const {
        return yOffset;
    }

    void setYOffset(int yOffset) {
        Map::yOffset = yOffset;
    }

private:
    int xOffset, yOffset;
};

#endif //SOCIETY_MAP_H
