//
// Created by Philip on 3/21/2020.
//


#include "WorldEntity.h"


MapNode::Ptr &WorldEntity::getPosition() {
    return position;
}

void WorldEntity::setPosition(MapNode::Ptr node) {
    position = std::move(node);
}

