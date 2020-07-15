//
// Created by Philip on 7/8/2020.
//

#ifndef SOCIETY_GOD_H
#define SOCIETY_GOD_H

#include "Actor.h"
#include "common/Body.h"
#include "macros.h"


class God {
public:
    God();

    void update();

    void generate_town();

    void generate_person();

    void generate_house();

    void add(const Body::Ptr& body);
private:
    std::vector<Actor::Ptr> actors;
};


#endif //SOCIETY_GOD_H
