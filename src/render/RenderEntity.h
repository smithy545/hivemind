//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RENDERENTITY_H
#define SOCIETY_RENDERENTITY_H

#include "collision/Rectangle.h"


class RenderEntity {
public:
    explicit RenderEntity(Rectangle bounds);

    RenderEntity(Rectangle bounds, double angle);

    RenderEntity(double x, double y, double width, double height, double angle);

    const Rectangle &getBounds() const;

    void setBounds(const Rectangle &bounds);

    double getAngle() const;

    void setAngle(double angle);

private:
    Rectangle bounds;
    double angle;
};


#endif //SOCIETY_RENDERENTITY_H
