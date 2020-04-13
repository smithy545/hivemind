//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RENDERENTITY_H
#define SOCIETY_RENDERENTITY_H

#include <glm/glm.hpp>


class RenderEntity {
public:
    RenderEntity(float x, float y);

    RenderEntity(const glm::vec3 &position);

    RenderEntity(float x, float y, float angle);

    RenderEntity(const glm::vec3 &position, float angle);

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &pos);

    float getAngle() const;

    void setAngle(float angle);

private:
    glm::vec3 pos;
    float angle;
};


#endif //SOCIETY_RENDERENTITY_H
