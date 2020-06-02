//
// Created by Philip on 6/1/2020.
//

#include "Body.h"

#include <iostream>


Body::Body() {}

void Body::update(float timeStep) {
    // update velocity
    velocity += acceleration * timeStep;

    // update position
    origin += velocity * timeStep;
}

const glm::vec3 &Body::getOrigin() const {
    return origin;
}

void Body::setOrigin(const glm::vec3 &origin) {
    Body::origin = origin;
}

const glm::vec3 &Body::getVelocity() const {
    return velocity;
}

void Body::setVelocity(const glm::vec3 &velocity) {
    Body::velocity = velocity;
}

const glm::vec3 &Body::getAcceleration() const {
    return acceleration;
}

void Body::setAcceleration(const glm::vec3 &acceleration) {
    Body::acceleration = acceleration;
}
