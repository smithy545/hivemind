//
// Created by Philip on 6/1/2020.
//

#include "Person.h"


const std::string &Person::getName() const {
    return name;
}

const glm::vec3 &Person::getPosition() const {
    return position;
}

void Person::setPosition(const glm::vec3 &position) {
    Person::position = position;
}
