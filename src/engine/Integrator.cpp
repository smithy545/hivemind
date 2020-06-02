//
// Created by Philip on 5/11/2020.
//

#include "Integrator.h"

#include <fmt/format.h>
#include <iostream>


Integrator::Integrator() {}

Integrator::Integrator(float timeStep, float friction) : timeStep(timeStep), friction(friction) {}

void Integrator::update(const std::vector<Body::Ptr> &bodies) {
    for(const auto& body: bodies) {
        auto bodyHash = getBodyHash(body);
        if(activeBodies.find(bodyHash) == activeBodies.end())
            activeBodies[bodyHash] = body;
    }

    for(const auto& bodyPair: activeBodies) {
        auto body = bodyPair.second;
        body->update(timeStep);

        // cull infinitesimal fields
        auto vel = body->getVelocity();
        vel.x = vel.x < EPSILON ? 0 : vel.x;
        vel.y = vel.y < EPSILON ? 0 : vel.y;
        vel.z = vel.z < EPSILON ? 0 : vel.z;
        body->setVelocity(vel);

        auto acc = body->getAcceleration();
        acc.x = acc.x < EPSILON ? 0 : acc.x;
        acc.y = acc.y < EPSILON ? 0 : acc.y;
        acc.z = acc.z < EPSILON ? 0 : acc.z;
        //body->setAcceleration(acc);
        body->setAcceleration({0, 0, 0});
    }
}

std::string Integrator::getBodyHash(const Body::Ptr& body) {
    return fmt::format("{0}:{1}:{2}", body->getOrigin().x, body->getOrigin().y, body->getOrigin().z);
}

