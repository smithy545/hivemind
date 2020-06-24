//
// Created by Philip on 5/11/2020.
//

#ifndef SOCIETY_INTEGRATOR_H
#define SOCIETY_INTEGRATOR_H

#include <string>
#include <unordered_map>

#include "collision/Body.h"
#include "macros.h"
#include "State.h"


class Integrator {
public:
    POINTERIZE(Integrator);

    void update(const std::vector<Body::Ptr> &bodies, float time_step);
private:
    const float EPSILON{0.01}; // Numbers with abs val smaller than this are considered equal to zero
    const glm::vec3 G{0, -0.01, 0}; // gravity acceleration vector
    std::unordered_map<std::string, Body::Ptr> active_bodies;
};


#endif //SOCIETY_INTEGRATOR_H
