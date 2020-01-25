//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_MAPNODE_H
#define HIVEMIND_MAPNODE_H

#include <memory>
#include <vector>

class MapNode {
public:
    typedef std::shared_ptr<MapNode> Ptr;

    MapNode(double x, double y) : MapNode(x, y, true, 8) {}
    MapNode(double x, double y, bool passable, int numNeighbors) : x(x), y(y), passable(passable), neighbors(numNeighbors) {}
    const double x;
    const double y;
    bool passable;
    std::vector<Ptr> neighbors;
};

#endif //HIVEMIND_MAPNODE_H
