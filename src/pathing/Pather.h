//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_PATHER_H
#define HIVEMIND_PATHER_H


#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include "src/pathing/MapNode.h"


class Pather {
public:
    class PathNode {
    public:
        typedef std::shared_ptr<PathNode> Ptr;

        PathNode(MapNode::Ptr pos, double g, double h, Ptr prev)
            : position(std::move(pos)), g(g), h(h), previous(std::move(prev)) {}

        double getF() {
            return g + h;
        }

        MapNode::Ptr position;
        double g;
        double h;
        Ptr previous;
    };

    static MapNode::MapPath genAStarPath(const MapNode::Ptr &start, const MapNode::Ptr &end);
private:
    static std::string genKey(const MapNode::Ptr &pos);
    static double distanceEuclid(const MapNode::Ptr &a, const MapNode::Ptr &b);
};


#endif //HIVEMIND_PATHER_H
