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
    _VAR(std::string,id,public,public,StringUtil::uuid4())
    _VAR(glm::vec3,origin,public,public,0)
    _VAR(glm::vec3,velocity,public,public,0)
    _VAR(glm::vec3,acceleration,public,public,0)
};


#endif //SOCIETY_BODY_H
