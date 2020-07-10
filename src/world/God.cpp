//
// Created by Philip on 7/8/2020.
//

#include "God.h"

#include "pathing/GridMap.h"


God::God() : map(std::make_shared<GridMap>(64,64)) {
    // let there be light
}

void God::update() {
    for(const auto& actor: actors) {
        actor->update();
    }
}

CollisionNode::Ptr God::get_collision_tree() {
    // kill nodes marked for removal
    auto node = collision_head;
    CollisionNode::Ptr prev = nullptr;
    while(node != nullptr) {
        if (!node->is_alive()) {
            if (prev != nullptr) {
                prev->set_next(node->get_next());
            } else {
                collision_head = node->get_next();
                if(collision_head == nullptr)
                    break;
            }
        }
        node = node->get_next();
        prev = node;
    }

    return collision_head;
}

void God::add(const PhysicsBody::Ptr& body, bool physics) {
    if(physics) {
        // find end of collision list
        auto collision_node = collision_head;
        while (collision_node != nullptr && collision_node->get_next() != nullptr)
            collision_node = collision_node->get_next();

        // add collision node with self to ensure collision is found and object is passed to integrator
        auto self_collision = std::make_shared<CollisionNode>(body, body);
        if (collision_node == nullptr) {
            collision_head = self_collision;
            collision_node = collision_head;
        } else {
            collision_node->set_next(self_collision);
            collision_node = collision_node->get_next();
        }
    }
}