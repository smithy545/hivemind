//
// Created by philip on 1/23/20.
//

#ifndef SOCIETY_PATHER_H
#define SOCIETY_PATHER_H

#include <memory>
#include <string>
#include <utility>

#include "GridNode.h"


class Pather {
public:
    class PathNode {
    public:
        typedef std::shared_ptr<PathNode> Ptr;

        PathNode(MapNode::Ptr pos, double g, double h, Ptr prev)
                : position(pos), g(g), h(h), previous(std::move(prev)) {}

        double getF() {
            return g + h;
        }

        MapNode::Ptr position;
        double g;
        double h;
        Ptr previous;
    };

    static MapNode::MapPath genAStarPath(const GridNode::Ptr &start, const GridNode::Ptr &end);
private:
    static std::string genKey(const MapNode::Ptr &pos);
    static double distanceEuclid(const MapNode::Ptr &a, const MapNode::Ptr &b);
};


#endif //SOCIETY_PATHER_H
