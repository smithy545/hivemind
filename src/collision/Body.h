//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_BODY_H
#define SOCIETY_BODY_H

#include <glm/glm.hpp>
#include <string>

#include "macros.h"


class Body {
public:
    POINTERIZE(Body);

    Body();

    void update(float timeStep);

    const std::string &getId() const;

    const glm::vec3 &getOrigin() const;

    void setOrigin(const glm::vec3 &origin);

    const glm::vec3 &getVelocity() const;

    void setVelocity(const glm::vec3 &velocity);

    const glm::vec3 &getAcceleration() const;

    void setAcceleration(const glm::vec3 &acceleration);
private:
    std::string id;
    glm::vec3 origin{0, 0, 0};
    glm::vec3 velocity{0, 0, 0}; // in meters I guess
    glm::vec3 acceleration{0, 0, 0};
};


#endif //SOCIETY_BODY_H
