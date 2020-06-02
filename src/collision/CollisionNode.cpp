//
// Created by Philip on 6/1/2020.
//

#include "CollisionNode.h"

CollisionNode::CollisionNode(Body::Ptr first, Body::Ptr second) : bodies(first, second) {}

Body::Ptr CollisionNode::getFirstBody() {
    return bodies.first;
}

Body::Ptr CollisionNode::getSecondBody() {
    return bodies.second;
}

CollisionNode::Ptr CollisionNode::getNext() {
    return CollisionNode::Ptr();
}
