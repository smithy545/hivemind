//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_ROBOT_H
#define HIVEMIND_ROBOT_H


#include <queue>
#include <memory>
#include "Map.h"

class Robot {
public:
    explicit Robot(Map::MapNode position);

    const std::queue<Map::MapNode> &Path() const;
    const Map::MapNode::Ptr &Position() const;

    void update();
protected:
    std::queue<Map::MapNode> path;
    Map::MapNode::Ptr position;
};


#endif //HIVEMIND_ROBOT_H
