//
// Created by Philip on 6/1/2020.
//

#include "CollisionNode.h"

#include <utility>


CollisionNode::CollisionNode(const PhysicsBody::Ptr& first, const PhysicsBody::Ptr& second) : CollisionNode(first, second, nullptr) {}

CollisionNode::CollisionNode(const PhysicsBody::Ptr& first, const PhysicsBody::Ptr& second, Ptr next) : bodies(first, second), _next(std::move(next)) {}

void CollisionNode::kill() {
    _alive = false;
}
