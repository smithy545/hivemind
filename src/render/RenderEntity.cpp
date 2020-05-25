//
// Created by smith on 4/12/2020.
//

#include "RenderEntity.h"

RenderEntity::RenderEntity(Rectangle bounds, double angle) : bounds(bounds), angle(angle) {}

RenderEntity::RenderEntity(Rectangle bounds) : RenderEntity(bounds, 0) {}

RenderEntity::RenderEntity(double x, double y, double width, double height, double angle)
        : RenderEntity({x, y, width, height}, angle) {}

const Rectangle &RenderEntity::getBounds() const {
    return bounds;
}

void RenderEntity::setBounds(const Rectangle &bounds) {
    RenderEntity::bounds = bounds;
}

double RenderEntity::getAngle() const {
    return angle;
}

void RenderEntity::setAngle(double angle) {
    RenderEntity::angle = angle;
}
