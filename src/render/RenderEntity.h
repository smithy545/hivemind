//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RENDERENTITY_H
#define SOCIETY_RENDERENTITY_H

#include "collision/Rectangle.h"


class RenderEntity {
public:
    explicit RenderEntity(Rectangle bounds);

    RenderEntity(Rectangle bounds, float angle);

    RenderEntity(double x, double y, double width, double height, float angle);

    const Rectangle &getBounds() const;

    void setBounds(const Rectangle &bounds);

    float getAngle() const;

    void setAngle(float angle);

private:
    Rectangle bounds;
    float angle;
};


#endif //SOCIETY_RENDERENTITY_H
