//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_COLLIDER_H
#define SOCIETY_COLLIDER_H

#include "macros.h"
#include "State.h"


class Collider {
public:
    POINTERIZE(Collider)

    virtual void update(State::Ptr state);
};


#endif //SOCIETY_COLLIDER_H
