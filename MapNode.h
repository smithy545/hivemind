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
    typedef std::vector<Ptr> MapPath;

    MapNode(int x, int y) : MapNode(x, y, true, 8) {}
    MapNode(int x, int y, bool passable, int numNeighbors) : x(x), y(y), passable(passable), neighbors(numNeighbors) {}

    const int x;
    const int y;
    bool passable;
    std::vector<Ptr> neighbors;
};

#endif //HIVEMIND_MAPNODE_H
