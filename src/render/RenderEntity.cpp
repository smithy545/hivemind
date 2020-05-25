//
// Created by smith on 4/12/2020.
//

#include "RenderEntity.h"

RenderEntity::RenderEntity(Rectangle bounds, float angle) : bounds(bounds), angle(angle) {}

RenderEntity::RenderEntity(Rectangle bounds) : RenderEntity(bounds, 0) {}

RenderEntity::RenderEntity(double x, double y, double width, double height, float angle)
        : RenderEntity({x, y, width, height}, angle) {}

const Rectangle &RenderEntity::getBounds() const {
    return bounds;
}

void RenderEntity::setBounds(const Rectangle &bounds) {
    RenderEntity::bounds = bounds;
}

float RenderEntity::getAngle() const {
    return angle;
}

void RenderEntity::setAngle(float angle) {
    RenderEntity::angle = angle;
}
