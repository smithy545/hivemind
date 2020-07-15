//
// Created by Philip on 7/8/2020.
//

#ifndef SOCIETY_GOD_H
#define SOCIETY_GOD_H

#include "Actor.h"
#include "collision/CollisionNode.h"
#include "macros.h"


class God {
public:
    God();

    void update();

    void generate_town();

    void generate_person();

    void generate_house();

    void add(const PhysicsBody::Ptr& body);

    CollisionNode::Ptr get_collision_tree();
private:
    CollisionNode::Ptr collision_head;
    std::vector<Actor::Ptr> actors;
};


#endif //SOCIETY_GOD_H
