//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_COLLISIONNODE_H
#define SOCIETY_COLLISIONNODE_H

#include <utility>

#include "collision/Body.h"
#include "macros.h"


class CollisionNode {
public:
    POINTERIZE(CollisionNode);

    CollisionNode(Body::Ptr first, Body::Ptr second);

    Body::Ptr getFirstBody();
    Body::Ptr getSecondBody();
    Ptr getNext();
private:
    std::pair<Body::Ptr, Body::Ptr> bodies;
    Ptr next;
};


#endif //SOCIETY_COLLISIONNODE_H
