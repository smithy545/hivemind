//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_PERSON_H
#define SOCIETY_PERSON_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "collision/Rectangle.h"
#include "macros.h"


class Person {
public:
    POINTERIZE(Person);

    const std::string &getName() const;

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

private:
    std::string name;
    glm::vec3 position;
};


#endif //SOCIETY_PERSON_H
