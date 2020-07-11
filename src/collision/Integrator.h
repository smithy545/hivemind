//
// Created by Philip on 5/11/2020.
//

#ifndef SOCIETY_INTEGRATOR_H
#define SOCIETY_INTEGRATOR_H

#include <string>
#include <unordered_map>

#include "collision/PhysicsBody.h"
#include "macros.h"
#include "engine/State.h"


class Integrator {
public:
    POINTERIZE(Integrator);

    void update(const std::vector<PhysicsBody::Ptr> &bodies, float time_step);
private:
    const float EPSILON{0.01}; // Numbers with abs val smaller than this are considered equal to zero
    const glm::vec3 G{0, -0.1, 0}; // gravity acceleration vector
    std::unordered_map<std::string, PhysicsBody::Ptr> active_bodies;
};


#endif //SOCIETY_INTEGRATOR_H
