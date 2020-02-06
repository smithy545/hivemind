//
// Created by Philip on 1/31/2020.
//

#ifndef HIVEMIND_VISIONMAP_H
#define HIVEMIND_VISIONMAP_H

#include "Map.h"
#include "MapNode.h"


class VisionMap : public Map {
public:
    typedef std::shared_ptr<VisionMap> Ptr;

    std::vector<MapNode::Ptr> getNodes() override;
    MapNode::Ptr getNode(int x, int y) override;
private:
    std::vector<MapNode::Ptr> nodes;
};


#endif //HIVEMIND_VISIONMAP_H
