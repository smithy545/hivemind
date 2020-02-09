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

    MapPosition(MapNode::Ptr position) : MapPosition(position, 0, 0) {}
    MapPosition(MapNode::Ptr position, double subX, double subY) : position(position), subPixelX(subX), subPixelY(subY) {}

    MapNode::Ptr position;
    double subPixelX;
    double subPixelY;
};


#endif //HIVEMIND_MAPPOSITION_H
