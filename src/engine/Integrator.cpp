//
// Created by Philip on 5/11/2020.
//

#include "Integrator.h"

#include <iostream>
#include <fmt/format.h>


void Integrator::update(const std::vector<Body::Ptr> &bodies, float time_step) {
    for(const auto& body: bodies) {
        if(active_bodies.find(body->get_id()) == active_bodies.end())
            active_bodies[body->get_id()] = body;
    }

    std::vector<std::string> inert_bodies;
    for(const auto& body_pair: active_bodies) {
        auto body = body_pair.second;
        body->update(time_step);

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
        if(pos.y > 0) {
            // if above ground accelerate due to gravity
            body->set_velocity(body->get_velocity() + G*time_step);
        } else if(pos.y < 0) {
            // if below ground warp to ground and freeze
            // TODO: should collide with ground?
            pos.y = 0;
            body->set_origin(pos);
            body->set_acceleration({0,0,0});
            body->set_velocity({0,0,0});
        }
        if (glm::all(glm::equal(body->get_velocity(), {0,0,0})) &&
            glm::all(glm::equal(body->get_acceleration(), {0,0,0})))
            inert_bodies.push_back(body->get_id());
    }

    // cull inert bodies
    for(const auto& id: inert_bodies)
        active_bodies.erase(id);
}
