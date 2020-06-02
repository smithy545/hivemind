//
// Created by Philip on 5/11/2020.
//

#include "Integrator.h"

#include <fmt/format.h>

Integrator::Integrator() {}

Integrator::Integrator(float timeStep) : timeStep(timeStep) {}

void Integrator::update(const std::vector<Body::Ptr> &bodies) {
    for(const auto& body: bodies) {
        auto bodyHash = getBodyHash(body);
        if(activeBodies.find(bodyHash) == activeBodies.end())
            activeBodies[bodyHash] = body;
    }

    std::vector<std::string> inertBodies;
    for(const auto& bodyPair: activeBodies) {
        auto body = bodyPair.second;
        body->update(timeStep);

        // cull infinitesimal fields
        auto vel = body->getVelocity();
        vel.x = glm::abs(vel.x) < EPSILON ? 0 : vel.x;
        vel.y = glm::abs(vel.y) < EPSILON ? 0 : vel.y;
        vel.z = glm::abs(vel.z) < EPSILON ? 0 : vel.z;
        body->setVelocity(vel);

        auto acc = body->getAcceleration();
        acc.x = glm::abs(acc.x) < EPSILON ? 0 : acc.x;
        acc.y = glm::abs(acc.y) < EPSILON ? 0 : acc.y;
        acc.z = glm::abs(acc.z) < EPSILON ? 0 : acc.z;
        body->setAcceleration(acc);

        auto pos = body->getOrigin();
        if(pos.y > 0) {
            // if above ground accelerate due to gravity
            body->setVelocity(body->getVelocity() + G*timeStep);
        } else if(pos.y < 0) {
            // if below ground warp to ground and freeze
            // TODO: should collide with ground?
            pos.y = 0;
            body->setOrigin(pos);
            body->setAcceleration({0,0,0});
            body->setVelocity({0,0,0});
        }

        if(glm::all(glm::equal(vel, {0,0,0}) + glm::equal(acc, {0,0,0})))
            inertBodies.push_back(getBodyHash(body));
    }
    for(const auto& hash: inertBodies)
        activeBodies.erase(hash);
}

std::string Integrator::getBodyHash(const Body::Ptr& body) {
    return fmt::format("{0}:{1}:{2}", body->getOrigin().x, body->getOrigin().y, body->getOrigin().z);
}

