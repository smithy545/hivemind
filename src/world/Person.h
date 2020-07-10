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
    POINTERIZE(Person);

    _MVAR_GETSET(std::string, name, public, public);
    _MVAR_GETSET(PhysicsBody::Ptr, body, public, public);

    void update() override;
};


#endif //SOCIETY_PERSON_H
