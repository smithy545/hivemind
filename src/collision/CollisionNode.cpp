//
// Created by Philip on 6/1/2020.
//

#include "CollisionNode.h"

#include <utility>


CollisionNode::CollisionNode(const Body::Ptr& first, const Body::Ptr& second) : CollisionNode(first, second, nullptr) {}

CollisionNode::CollisionNode(const Body::Ptr& first, const Body::Ptr& second, Ptr next) : bodies(first, second), next(std::move(next)), alive(true) {}

Body::Ptr CollisionNode::getFirstBody() {
    return bodies.first;
}

Body::Ptr CollisionNode::getSecondBody() {
    return bodies.second;
}

CollisionNode::Ptr CollisionNode::getNext() {
    return next;
}

void CollisionNode::setNext(CollisionNode::Ptr node) {
    next = std::move(node);
}

void CollisionNode::kill() {
    alive = false;
}

bool CollisionNode::isAlive() {
    return alive;
}