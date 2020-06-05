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

    CollisionNode(const Body::Ptr& first, const Body::Ptr& second);
    CollisionNode(const Body::Ptr& first, const Body::Ptr& second, Ptr next);

    Body::Ptr getFirstBody();
    Body::Ptr getSecondBody();
    Ptr getNext();
    void setNext(Ptr node);
    void kill();
    bool isAlive();
private:
    bool alive;
    std::pair<Body::Ptr, Body::Ptr> bodies;
    Ptr next;
};


#endif //SOCIETY_COLLISIONNODE_H
