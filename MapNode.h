//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_MAPNODE_H
#define HIVEMIND_MAPNODE_H

#include <memory>
#include <vector>

class MapEntity;

class MapNode {
public:
    typedef std::shared_ptr<MapNode> Ptr;
    typedef std::vector<Ptr> MapPath;

    MapNode(int x, int y) : MapNode(x, y, true) {}
    MapNode(int x, int y, bool passable) : x(x), y(y), passable(passable) {}

    const int x;
    const int y;
    bool passable;
    std::vector<Ptr> neighbors;
    std::vector<std::shared_ptr<MapEntity>> entities;
};

#endif //HIVEMIND_MAPNODE_H
