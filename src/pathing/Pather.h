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
        PTR(PathNode);

        PathNode(MapNode::Ptr pos, double g, double h, Ptr prev)
                : position(std::move(pos)), g(g), h(h), previous(std::move(prev)) {}

        double get_f() {
            return g + h;
        }

        MapNode::Ptr position;
        double g;
        double h;
        Ptr previous;
    };

    static MapNode::MapPath get_astar_path(const TopologicalMapNode::Ptr &start, const TopologicalMapNode::Ptr &end);

    static MapNode::MapPath get_astar_path(const Map::Ptr &map, const MapNode::Ptr &start, const MapNode::Ptr &end);
private:
    static std::string get_node_key(const MapNode::Ptr &pos);

    static double distance_euclid(const MapNode::Ptr &a, const MapNode::Ptr &b);
};


#endif //SOCIETY_PATHER_H
