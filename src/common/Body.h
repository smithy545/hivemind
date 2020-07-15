//
// Created by Philip on 7/10/2020.
//

#ifndef SOCIETY_BODY_H
#define SOCIETY_BODY_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

#include "macros.h"
#include "util/StringUtil.h"


class Body {
public:
    POINTERIZE(Body);

    virtual glm::mat4 get_model_matrix() {
        return glm::translate(glm::mat4(1), _position);
    }

    virtual bool is_dirty() {
        return true;
    }

    CONSTVAR(std::string, id, public){StringUtil::uuid4()};
    REFVAR(glm::vec3, position, public, public){0}; // in meters I guess
};


#endif //SOCIETY_BODY_H
