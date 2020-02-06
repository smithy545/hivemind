//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_HUMAN_H
#define HIVEMIND_HUMAN_H


#include <queue>
#include <memory>
#include "MapNode.h"
#include "VisionMap.h"


class Human {
public:
    explicit Human(const MapNode& position);

    const std::queue<MapNode> &Path() const;
    const MapNode::Ptr &Position() const;

    void update();
protected:
    std::queue<MapNode> path;
    MapNode::Ptr position;
    VisionMap::Ptr visionMap;
};


#endif //HIVEMIND_HUMAN_H
