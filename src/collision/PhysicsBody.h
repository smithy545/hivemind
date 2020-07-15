//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_PHYSICSBODY_H
#define SOCIETY_PHYSICSBODY_H

#include <glm/glm.hpp>
#include <string>

#include "common/Body.h"
#include "macros.h"


class PhysicsBody : public Body {
public:
    POINTERIZE(PhysicsBody);

    void update(float time_step);

    VAR(glm::vec3, velocity, public, public){0};
    VAR(glm::vec3, acceleration, public, public){0};
};


#endif //SOCIETY_PHYSICSBODY_H
