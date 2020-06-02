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

    CollisionNode(const Body::Ptr& first, const Body::Ptr& second);
    CollisionNode(const Body::Ptr& first, const Body::Ptr& second, Ptr prev, Ptr next);

    Body::Ptr getFirstBody();
    Body::Ptr getSecondBody();
    Ptr getNext();
    void setNext(Ptr next);

    const Ptr &getPrev() const;

    void setPrev(const Ptr &prev);

private:
    std::pair<Body::Ptr, Body::Ptr> bodies;
    Ptr prev, next;
};


#endif //SOCIETY_COLLISIONNODE_H
