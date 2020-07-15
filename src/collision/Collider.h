//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_COLLIDER_H
#define SOCIETY_COLLIDER_H

#include <vector>

#include "collision/PhysicsBody.h"
#include "collision/CollisionNode.h"
#include "macros.h"


class Collider {
public:
    PTR(Collider);

    std::vector<PhysicsBody::Ptr> update(CollisionNode::Ptr collisionTree);
};


#endif //SOCIETY_COLLIDER_H
