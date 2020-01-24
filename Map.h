//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_MAP_H
#define HIVEMIND_MAP_H

#include <memory>
#include <vector>

class Map {
public:
    typedef std::shared_ptr<Map> Ptr;

    class MapNode {
        public:
            typedef std::shared_ptr<MapNode> Ptr;
            MapNode(double x, double y) : MapNode(x, y, true) {}
            MapNode(double x, double y, bool passable) : x(x), y(y), passable(passable) {}
            const double x;
            const double y;
            bool passable;
    };
    virtual std::vector<MapNode::Ptr> getNeighbors(MapNode::Ptr position) = 0;
};

#endif //HIVEMIND_MAP_H
