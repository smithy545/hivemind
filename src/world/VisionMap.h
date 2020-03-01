//
// Created by Philip on 1/31/2020.
//

#ifndef HIVEMIND_VISIONMAP_H
#define HIVEMIND_VISIONMAP_H

#include "src/pathing/Map.h"
#include "src/world/MapActor.h"
#include "src/pathing/MapNode.h"


class VisionMap : public Map {
public:
    typedef std::shared_ptr<VisionMap> Ptr;

    MapNode::Ptr getNode(int x, int y) override;

    const std::vector<MapNode::Ptr> &getNodes() override {
        return nodes;
    }

private:
    std::vector<MapNode::Ptr> nodes;
};


#endif //HIVEMIND_VISIONMAP_H
