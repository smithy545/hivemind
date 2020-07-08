//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_PERSON_H
#define SOCIETY_PERSON_H

#include <glm/glm.hpp>
#include <string>

#include "macros.h"


class Person {
public:
    POINTERIZE(Person);

    _MVAR_GETSET(name, std::string, public, public)
    _VAR_GETSET(position, glm::vec3, public, public)
};


#endif //SOCIETY_PERSON_H
