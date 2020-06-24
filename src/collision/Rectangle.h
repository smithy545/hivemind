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

    void set_x(double x);

    void set_y(double y);

    void set_width(double width);

    void set_height(double height);

    _VAR_GET(x, double, public)
    _VAR_GET(y, double, public)
    _VAR_GET(width, double, public)
    _VAR_GET(height, double, public)
    _VAR_GET_INIT(points, std::vector<glm::vec2>, public, 4)
private:
    void calculate_points();
};


#endif //SOCIETY_RECTANGLE_H
