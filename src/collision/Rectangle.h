//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RECTANGLE_H
#define SOCIETY_RECTANGLE_H

#include <glm/glm.hpp>
#include <vector>

#include "Bound.h"
#include "macros.h"


class Rectangle : public Bound, public std::enable_shared_from_this<Rectangle> {
public:
    POINTERIZE(Rectangle);

    Rectangle(double width, double height);

    Rectangle(double x, double y, double width, double height);

    bool collides(double X, double Y) const;

    bool collides(Bound::Ptr other) override;

    double get_center_x();

    double get_center_y();

    _VAR(double,x,public,public,)
    _VAR(double,y,public,public,)
    _VAR(double,width,public,public,)
    _VAR(double,height,public,public,)
    _VAR(std::vector<glm::vec2>,points,public,private,4)
private:
    void calculatePoints();
};


#endif //SOCIETY_RECTANGLE_H
