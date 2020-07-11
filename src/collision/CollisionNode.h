//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_COLLISIONNODE_H
#define SOCIETY_COLLISIONNODE_H

#include <utility>

#include "collision/PhysicsBody.h"
#include "macros.h"


class CollisionNode{
public:
    POINTERIZE(CollisionNode);
    typedef std::pair<PhysicsBody::Ptr, PhysicsBody::Ptr> CollisionPair;

    CollisionNode(const PhysicsBody::Ptr& first, const PhysicsBody::Ptr& second);
    CollisionNode(const PhysicsBody::Ptr& first, const PhysicsBody::Ptr& second, Ptr next);

    void kill();

    PhysicsBody::Ptr get_first_body();

    PhysicsBody::Ptr get_second_body();

    _MVAR_GETSET(CollisionNode::Ptr, next, public, public);
    _BVAR_GET(alive, public){true};
private:
    CollisionPair bodies;
};


#endif //SOCIETY_COLLISIONNODE_H
