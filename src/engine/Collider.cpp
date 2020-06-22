//
// Created by smith on 4/12/2020.
//

#include "Collider.h"

#include <iostream>
#include <utility>


std::vector<Body::Ptr> Collider::update(CollisionNode::Ptr collision_tree) {
    std::vector<Body::Ptr> collisions;
    auto node = std::move(collision_tree);
    while(node != nullptr) {
        if(node->getFirstBody()->get_id() == node->getSecondBody()->get_id()) {
            // self collision
            collisions.push_back(node->getFirstBody());
            node->kill();
        } else {
            auto collided = false;

            // TODO: Check collisions here

            if (collided) {
                collisions.push_back(node->getFirstBody());
                collisions.push_back(node->getSecondBody());
            }
            node->kill();
        }
        node = node->get_next();
    }
    return collisions;
}
