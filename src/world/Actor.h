//
// Created by Philip on 7/10/2020.
//

#ifndef SOCIETY_ACTOR_H
#define SOCIETY_ACTOR_H

#include "macros.h"


class Actor {
public:
    POINTERIZE(Actor);

    virtual void update() = 0;
};


#endif //SOCIETY_ACTOR_H
