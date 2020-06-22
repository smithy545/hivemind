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
    PVAR(std::string, name, public, public)
    PVAR(glm::vec3, position, public, public)
};


#endif //SOCIETY_PERSON_H
