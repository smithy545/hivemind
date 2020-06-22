//
// Created by Philip on 6/1/2020.
//

#include "CollisionNode.h"

#include <utility>


CollisionNode::CollisionNode(const Body::Ptr& first, const Body::Ptr& second) : CollisionNode(first, second, nullptr) {}

CollisionNode::CollisionNode(const Body::Ptr& first, const Body::Ptr& second, Ptr next) : _bodies(first, second), _next(std::move(next)) {}

Body::Ptr CollisionNode::get_first_body() {
    return _bodies.first;
}

Body::Ptr CollisionNode::get_second_body() {
    return _bodies.second;
}

void CollisionNode::kill() {
    _alive = false;
}
