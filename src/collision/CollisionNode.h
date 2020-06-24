//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_COLLISIONNODE_H
#define SOCIETY_COLLISIONNODE_H

#include <utility>

#include "collision/Body.h"
#include "macros.h"


class CollisionNode : public std::enable_shared_from_this<CollisionNode> {
public:
    POINTERIZE(CollisionNode);
    typedef std::pair<Body::Ptr, Body::Ptr> CollisionPair;

    CollisionNode(const Body::Ptr& first, const Body::Ptr& second);
    CollisionNode(const Body::Ptr& first, const Body::Ptr& second, Ptr next);

    void kill();

    inline Body::Ptr get_first_body() {
        return bodies.first;
    }

    inline Body::Ptr get_second_body() {
        return bodies.second;
    }

    _MVAR_GETSET(next, CollisionNode::Ptr, public, public)
    _BVAR_GET_INIT(alive, public, true)
private:
    CollisionPair bodies;
};


#endif //SOCIETY_COLLISIONNODE_H
