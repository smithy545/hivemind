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

    Body::Ptr get_first_body();
    Body::Ptr get_second_body();
    void kill();
private:
    _VAR(CollisionPair,bodies,private,private,)
    _VAR(Ptr,next,public,public,)
    _BVAR(bool,alive,public,private,true)
};


#endif //SOCIETY_COLLISIONNODE_H
