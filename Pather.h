//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_PATHER_H
#define HIVEMIND_PATHER_H


#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "MapNode.h"


class Pather {
public:
    class PathingNode {
    public:
        typedef std::shared_ptr<PathingNode> Ptr;

        PathingNode(MapNode::Ptr pos, double g, double h, Ptr prev)
            : position(std::move(pos)), g(g), h(h), previous(std::move(prev)) {}

        double getF() {
            return g + h;
        }

        MapNode::Ptr position;
        double g;
        double h;
        Ptr previous;
    };

    std::vector<MapNode::Ptr> genAStarPath(const MapNode::Ptr &start, const MapNode::Ptr &end);
private:
    std::string genKey(const MapNode::Ptr &pos);
    double distanceEuclid(const MapNode::Ptr &a, const MapNode::Ptr &b);
};


#endif //HIVEMIND_PATHER_H
