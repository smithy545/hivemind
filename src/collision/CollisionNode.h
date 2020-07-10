//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_COLLISIONNODE_H
#define SOCIETY_COLLISIONNODE_H

#include <utility>

#include "collision/PhysicsBody.h"
#include "macros.h"


class CollisionNode : public std::enable_shared_from_this<CollisionNode> {
public:
    POINTERIZE(CollisionNode);
    typedef std::pair<PhysicsBody::Ptr, PhysicsBody::Ptr> CollisionPair;

    CollisionNode(const PhysicsBody::Ptr& first, const PhysicsBody::Ptr& second);
    CollisionNode(const PhysicsBody::Ptr& first, const PhysicsBody::Ptr& second, Ptr next);

    void kill();

    inline PhysicsBody::Ptr get_first_body() {
        return bodies.first;
    }

    inline PhysicsBody::Ptr get_second_body() {
        return bodies.second;
    }

    _MVAR_GETSET(CollisionNode::Ptr, next, public, public);
    _BVAR_GET(alive, public){true};
private:
    CollisionPair bodies;
};


#endif //SOCIETY_COLLISIONNODE_H
