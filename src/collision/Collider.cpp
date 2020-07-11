//
// Created by smith on 4/12/2020.
//

#include "Collider.h"

#include <utility>


std::vector<PhysicsBody::Ptr> Collider::update(CollisionNode::Ptr collision_tree) {
    std::vector<PhysicsBody::Ptr> collisions;
    auto node = std::move(collision_tree);
    while(node != nullptr) {
        if(node->get_first_body()->get_id() == node->get_second_body()->get_id()) {
            // self collision
            collisions.push_back(node->get_first_body());
            node->kill();
        } else {
            auto collided = false;

            // TODO: Check collisions here

            if (collided) {
                collisions.push_back(node->get_first_body());
                collisions.push_back(node->get_second_body());
            }
            node->kill();
        }
        node = node->get_next();
    }
    return collisions;
}
