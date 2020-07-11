//
// Created by Philip on 7/10/2020.
//

#ifndef SOCIETY_BODY_H
#define SOCIETY_BODY_H

#include <glm/glm.hpp>

#include "macros.h"
#include "util/StringUtil.h"


class Body {
public:
    POINTERIZE(Body);
    // in meters I guess
    _VAR_GET(std::string, id, public){StringUtil::uuid4()};
    _VAR_GETSET(glm::vec3, origin, public, public){0};
};


#endif //SOCIETY_BODY_H
