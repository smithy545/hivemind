//
// Created by Philip on 6/1/2020.
//

#include "CollisionNode.h"

#include <utility>


CollisionNode::CollisionNode(const Body::Ptr& first, const Body::Ptr& second) : CollisionNode(first, second, nullptr, nullptr) {}

CollisionNode::CollisionNode(const Body::Ptr& first, const Body::Ptr& second, Ptr prev, Ptr next) : bodies(first, second), prev(std::move(prev)), next(std::move(next)) {}

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

const CollisionNode::Ptr &CollisionNode::getPrev() const {
    return prev;
}

void CollisionNode::setPrev(const CollisionNode::Ptr &prev) {
    this->prev = prev;
}
