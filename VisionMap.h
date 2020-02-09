//
// Created by Philip on 1/31/2020.
//

#ifndef HIVEMIND_VISIONMAP_H
#define HIVEMIND_VISIONMAP_H

#include "Map.h"
#include "MapActor.h"
#include "MapNode.h"


class VisionMap : public Map {
public:
    typedef std::shared_ptr<VisionMap> Ptr;

    MapNode::Ptr getNode(int x, int y) override;

    std::vector<MapActor::Ptr> VisionMap::getActors() override {
        return actors;
    }

    std::vector<MapNode::Ptr> VisionMap::getNodes() override {
        return nodes;
    }

private:
    std::vector<MapActor::Ptr> actors;
    std::vector<MapNode::Ptr> nodes;
};


#endif //HIVEMIND_VISIONMAP_H
