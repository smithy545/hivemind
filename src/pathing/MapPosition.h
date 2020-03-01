//
// Created by Philip on 2/8/2020.
//

#ifndef HIVEMIND_MAPPOSITION_H
#define HIVEMIND_MAPPOSITION_H

#include <memory>
#include <utility>

#include "MapNode.h"


class MapPosition {
public:
    typedef std::shared_ptr<MapPosition> Ptr;

    explicit MapPosition(MapNode::Ptr mapNode) : MapPosition(std::move(mapNode), 0, 0) {}

    MapPosition(MapNode::Ptr mapNode, double subX, double subY) : mapNode(std::move(mapNode)), subPixelX(subX),
                                                                  subPixelY(subY) {}

    MapNode::Ptr getNode() {
        return mapNode;
    }

    void setNode(const MapNode::Ptr &node) {
        this->mapNode = node;
    }

    double getSubPixelX() const {
        return subPixelX;
    }

    void setSubPixelX(double subPixelX) {
        this->subPixelX = subPixelX;
    }

    double getSubPixelY() const {
        return subPixelY;
    }

    void setSubPixelY(double subPixelY) {
        this->subPixelY = subPixelY;
    }

private:
    MapNode::Ptr mapNode;
    double subPixelX;
    double subPixelY;
};


#endif //HIVEMIND_MAPPOSITION_H
