//
// Created by Philip on 5/11/2020.
//

#ifndef SOCIETY_INTEGRATOR_H
#define SOCIETY_INTEGRATOR_H

#include "macros.h"
#include "State.h"

class Integrator {
public:
    POINTERIZE(Integrator)

    virtual void update(State::Ptr state);
};


#endif //SOCIETY_INTEGRATOR_H
