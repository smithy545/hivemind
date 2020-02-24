//
// Created by Philip on 2/8/2020.
//

#ifndef HIVEMIND_MAPPOSITION_H
#define HIVEMIND_MAPPOSITION_H

#include <memory>

#include "MapNode.h"


class MapPosition {
public:
    typedef std::shared_ptr<MapPosition> Ptr;

    MapPosition(MapNode::Ptr mapNode) : MapPosition(mapNode, 0, 0) {}
    MapPosition(MapNode::Ptr mapNode, double subX, double subY) : node(mapNode), subPixelX(subX), subPixelY(subY) {}

    MapNode::Ptr node;
    double subPixelX;
    double subPixelY;
};


#endif //HIVEMIND_MAPPOSITION_H
