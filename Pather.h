//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_PATHER_H
#define HIVEMIND_PATHER_H


#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Map.h"


class Pather {
public:
    class PathingNode {
    public:
        typedef std::shared_ptr<PathingNode> Ptr;

        PathingNode(Map::MapNode::Ptr pos, double g, double h, Ptr prev)
            : position(std::move(pos)), g(g), h(h), previous(std::move(prev)) {}

        double getF() {
            return g + h;
        }

        Map::MapNode::Ptr position;
        double g;
        double h;
        Ptr previous;
    };

    std::vector<Map::MapNode::Ptr> genAStarPath(const Map::Ptr &map, const Map::MapNode::Ptr &start, const Map::MapNode::Ptr &end);
private:
    std::string genKey(const Map::MapNode::Ptr &pos);
    double distanceEuclid(const Map::MapNode::Ptr &a, const Map::MapNode::Ptr &b);
};


#endif //HIVEMIND_PATHER_H
