//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_BODY_H
#define SOCIETY_BODY_H

#include <glm/glm.hpp>
#include <string>

#include "macros.h"
#include "util/StringUtil.h"

class Body {
public:
    POINTERIZE(Body);

    void update(float time_step);

    // in meters I guess
    _VAR_GET_INIT(id, std::string, public, StringUtil::uuid4())
    _VAR_GETSET_INIT(origin, glm::vec3, public, public, 0)
    _VAR_GETSET_INIT(velocity, glm::vec3, public, public, 0)
    _VAR_GETSET_INIT(acceleration, glm::vec3, public, public, 0)
};


#endif //SOCIETY_BODY_H
