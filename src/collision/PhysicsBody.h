//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_PHYSICSBODY_H
#define SOCIETY_PHYSICSBODY_H

#include <glm/glm.hpp>
#include <string>

#include "common/Body.h"
#include "macros.h"
#include "util/StringUtil.h"

class PhysicsBody : Body {
public:
    POINTERIZE(PhysicsBody);

    void update(float time_step);

    // in meters I guess
    _VAR_GET(std::string, id, public){StringUtil::uuid4()};
    _VAR_GETSET(glm::vec3, origin, public, public){0};
    _VAR_GETSET(glm::vec3, velocity, public, public){0};
    _VAR_GETSET(glm::vec3, acceleration, public, public){0};
};


#endif //SOCIETY_PHYSICSBODY_H
