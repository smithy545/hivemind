//
// Created by smith on 4/12/2020.
//

#include "Collider.h"


std::vector<Body::Ptr> Collider::update(CollisionNode::Ptr collisionTree) {
    auto touchedBodies = std::vector<Body::Ptr>();
    while(collisionTree != nullptr) {
        bool collided = true;
        if(collided) {
            touchedBodies.push_back(collisionTree->getFirstBody());
            touchedBodies.push_back(collisionTree->getSecondBody());
        }
        collisionTree = collisionTree->getNext();
    }
    return touchedBodies;
}
