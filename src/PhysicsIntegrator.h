//
// Created by Philip on 5/11/2020.
//

#ifndef SOCIETY_PHYSICSINTEGRATOR_H
#define SOCIETY_PHYSICSINTEGRATOR_H

#include <memory>

#include "GameState.h"

class PhysicsIntegrator {
public:
    typedef std::shared_ptr<PhysicsIntegrator> Ptr;

    virtual void update(GameState::Ptr state);
};


#endif //SOCIETY_PHYSICSINTEGRATOR_H
