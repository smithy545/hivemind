//
// Created by smith on 4/12/2020.
//

#include "RenderEntity.h"


RenderEntity::RenderEntity(float x, float y) : RenderEntity(x, y, 0) {}

RenderEntity::RenderEntity(const glm::vec3 &position, float angle) : pos(position), angle(angle) {}

RenderEntity::RenderEntity(float x, float y, float angle) : pos(x, y, 0), angle(angle) {}

const glm::vec3 &RenderEntity::getPosition() const {
    return pos;
}

void RenderEntity::setPosition(const glm::vec3 &pos) {
    RenderEntity::pos = pos;
}

float RenderEntity::getAngle() const {
    return angle;
}

void RenderEntity::setAngle(float angle) {
    RenderEntity::angle = angle;
}
