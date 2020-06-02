//
// Created by smith on 4/12/2020.
//

#include "Collider.h"

#include <utility>


std::vector<Body::Ptr> Collider::update(CollisionNode::Ptr collisionTree) {
    auto touchedBodies = std::vector<Body::Ptr>();
    auto node = std::move(collisionTree);
    while(node != nullptr) {
        auto collided = false;
        // only bare minimum collision detection
        if(node->getFirstBody() == node->getSecondBody())
            collided = true;

        if(collided) {
            touchedBodies.push_back(node->getFirstBody());
            touchedBodies.push_back(node->getSecondBody());
        } else {
            // no collision, remove from tree
            if(node->getPrev() != nullptr)
                node->getPrev()->setNext(node->getNext());
            if(node->getNext() != nullptr)
                node->getNext()->setPrev(node->getPrev());
        }
        node = node->getNext();
    }
    return touchedBodies;
}
