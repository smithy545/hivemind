//
// Created by Philip on 6/1/2020.
//

#include "PhysicsBody.h"


void PhysicsBody::update(float time_step) {
    // update velocity
    _velocity += _acceleration * time_step;

    // update position
    _origin += _velocity * time_step;
}
