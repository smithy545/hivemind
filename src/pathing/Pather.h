//
// Created by philip on 1/23/20.
//

#ifndef SOCIETY_PATHER_H
#define SOCIETY_PATHER_H

#include <string>
#include <utility>

#include "macros.h"
#include "Map.h"
#include "MapNode.h"


class Pather {
public:
    class PathNode {
    public:
        POINTERIZE(PathNode);

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

    static MapNode::MapPath genAStarPath(const TopologicalMapNode::Ptr &start, const TopologicalMapNode::Ptr &end);

    static MapNode::MapPath genAStarPath(const Map::Ptr &map, const MapNode::Ptr &start, const MapNode::Ptr &end);

private:
    static std::string genKey(const MapNode::Ptr &pos);

    static double distanceEuclid(const MapNode::Ptr &a, const MapNode::Ptr &b);
};


#endif //SOCIETY_PATHER_H
