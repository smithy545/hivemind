//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_COLLIDER_H
#define SOCIETY_COLLIDER_H

#include <memory>

#include "State.h"


class Collider {
public:
    typedef std::shared_ptr<Collider> Ptr;

    virtual void update(State::Ptr state);
};


#endif //SOCIETY_COLLIDER_H
