//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_MAP_H
#define HIVEMIND_MAP_H

#include <vector>

class Map {
public:
    class MapNode {
        public:
            typedef std::shared_ptr<MapNode> Ptr;
            MapNode(double x, double y) : x(x), y(y) {}
            const double x;
            const double y;
    };
protected:
    virtual std::vector<MapNode> getNeighbors(MapNode position) = 0;
};

#endif //HIVEMIND_MAP_H
