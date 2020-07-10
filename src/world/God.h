//
// Created by Philip on 7/8/2020.
//

#ifndef SOCIETY_GOD_H
#define SOCIETY_GOD_H

#include "Actor.h"
#include "collision/CollisionNode.h"
#include "macros.h"
#include "pathing/Map.h"


class God {
public:
    POINTERIZE(God);

    God();

    void update();

    void add(const PhysicsBody::Ptr& body, bool physics);

    CollisionNode::Ptr get_collision_tree();
private:
    CollisionNode::Ptr collision_head;
    Map::Ptr map;
    std::vector<Actor::Ptr> actors;
};


#endif //SOCIETY_GOD_H
