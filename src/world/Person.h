//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_PERSON_H
#define SOCIETY_PERSON_H

#include <glm/glm.hpp>
#include <string>

#include "Actor.h"
#include "collision/PhysicsBody.h"
#include "macros.h"


class Person : public Actor {
public:
    PTR(Person);

    MVAR(std::string, name, public, public);
    MVAR(PhysicsBody::Ptr, body, public, public);

    void update() override;
};


#endif //SOCIETY_PERSON_H
