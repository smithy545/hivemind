//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_PHYSICSCOLLIDER_H
#define SOCIETY_PHYSICSCOLLIDER_H

#include <memory>

#include "GameState.h"


class PhysicsCollider {
public:
    typedef std::shared_ptr<PhysicsCollider> Ptr;

    virtual void update(GameState::Ptr state);
};


#endif //SOCIETY_PHYSICSCOLLIDER_H
