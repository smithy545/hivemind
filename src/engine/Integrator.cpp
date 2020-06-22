//
// Created by Philip on 5/11/2020.
//

#include "Integrator.h"

#include <iostream>
#include <fmt/format.h>


Integrator::Integrator(float timeStep) : timeStep(timeStep) {}

void Integrator::update(const std::vector<Body::Ptr> &bodies) {
    for(const auto& body: bodies) {
        if(activeBodies.find(body->get_id()) == activeBodies.end())
            activeBodies[body->get_id()] = body;
    }

    std::vector<std::string> inertBodies;
    for(const auto& bodyPair: activeBodies) {
        auto body = bodyPair.second;
        body->update(timeStep);

        // cull infinitesimal fields
        auto vel = body->get_velocity();
        vel.x = glm::abs(vel.x) < EPSILON ? 0 : vel.x;
        vel.y = glm::abs(vel.y) < EPSILON ? 0 : vel.y;
        vel.z = glm::abs(vel.z) < EPSILON ? 0 : vel.z;
        body->set_velocity(vel);

        auto acc = body->get_acceleration();
        acc.x = glm::abs(acc.x) < EPSILON ? 0 : acc.x;
        acc.y = glm::abs(acc.y) < EPSILON ? 0 : acc.y;
        acc.z = glm::abs(acc.z) < EPSILON ? 0 : acc.z;
        body->set_acceleration(acc);

        auto pos = body->get_origin();
        if(pos.y > groundLevel) {
            // if above ground accelerate due to gravity
            body->set_velocity(body->get_velocity() + G*timeStep);
        } else if(pos.y < groundLevel) {
            // if below ground warp to ground and freeze
            // TODO: should collide with ground?
            pos.y = 0;
            body->set_origin(pos);
            body->set_acceleration({0,0,0});
            body->set_velocity({0,0,0});
        }
        if (glm::all(glm::equal(body->get_velocity(), {0,0,0})) &&
            glm::all(glm::equal(body->get_acceleration(), {0,0,0})))
            inertBodies.push_back(body->get_id());
    }

    // cull inert bodies
    for(const auto& id: inertBodies)
        activeBodies.erase(id);
}
