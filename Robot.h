//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_ROBOT_H
#define HIVEMIND_ROBOT_H


#include <queue>
#include <memory>
#include "MapNode.h"

class Robot {
public:
    explicit Robot(MapNode position);

    const std::queue<MapNode> &Path() const;
    const MapNode::Ptr &Position() const;

    void update();
protected:
    std::queue<MapNode> path;
    MapNode::Ptr position;
};


#endif //HIVEMIND_ROBOT_H
