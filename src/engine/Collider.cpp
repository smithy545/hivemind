//
// Created by smith on 4/12/2020.
//

#include "Collider.h"

#include <iostream>
#include <utility>


std::vector<Body::Ptr> Collider::update(CollisionNode::Ptr collisionTree) {
    std::vector<Body::Ptr> collisions;
    auto node = std::move(collisionTree);
    while(node != nullptr) {
        if(node->getFirstBody()->getId() == node->getSecondBody()->getId()) {
            // self collision
            collisions.push_back(node->getFirstBody());
            node->kill();
        } else {
            auto collided = false;

            // TODO: Check collisions here

            if (collided) {
                collisions.push_back(node->getFirstBody());
                collisions.push_back(node->getSecondBody());
            } else
                node->kill();
        }
        node = node->getNext();
    }
    return collisions;
}
