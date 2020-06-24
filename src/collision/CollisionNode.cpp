//
// Created by Philip on 6/1/2020.
//

#include "CollisionNode.h"

#include <utility>


CollisionNode::CollisionNode(const Body::Ptr& first, const Body::Ptr& second) : CollisionNode(first, second, nullptr) {}

CollisionNode::CollisionNode(const Body::Ptr& first, const Body::Ptr& second, Ptr next) : bodies(first, second), _next(std::move(next)) {}

void CollisionNode::kill() {
    _alive = false;
}
