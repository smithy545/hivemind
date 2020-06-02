//
// Created by Philip on 6/1/2020.
//

#include "CollisionNode.h"

#include <utility>


CollisionNode::CollisionNode(const Body::Ptr& first, const Body::Ptr& second) : CollisionNode(first, second, nullptr) {}

CollisionNode::CollisionNode(const Body::Ptr& first, const Body::Ptr& second, CollisionNode::Ptr next) : bodies(first, second), next(std::move(next)) {}

Body::Ptr CollisionNode::getFirstBody() {
    return bodies.first;
}

Body::Ptr CollisionNode::getSecondBody() {
    return bodies.second;
}

CollisionNode::Ptr CollisionNode::getNext() {
    return CollisionNode::Ptr();
}

void CollisionNode::setNext(CollisionNode::Ptr next) {
    this->next = next;
}
