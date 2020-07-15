//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_PERSON_H
#define SOCIETY_PERSON_H

#include <glm/glm.hpp>
#include <string>

#include "Actor.h"
#include "common/Body.h"
#include "macros.h"


class Person : public Actor {
public:
    MVAR(std::string, name, public, public);
    MVAR(Body::Ptr, body, public, public);

    void update() override;
};


#endif //SOCIETY_PERSON_H
