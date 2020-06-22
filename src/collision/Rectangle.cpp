//
// Created by smith on 4/12/2020.
//

#include "Rectangle.h"


Rectangle::Rectangle(double width, double height) : Rectangle(0, 0, width, height) {}

Rectangle::Rectangle(double x, double y, double width, double height) : _x(x), _y(y),
                                                                        _width(width), _height(height) {
    calculatePoints();
}

bool Rectangle::collides(double X, double Y) const {
    return X >= _x && X < _x + _width && Y >= _y && Y < _y + _height;
}

bool Rectangle::collides(Bound::Ptr other) {
    auto rect = std::dynamic_pointer_cast<Rectangle>(other);
    if(rect != nullptr) {
        if(rect->collides(this->shared_from_this()))
            return true;
        for (auto p: rect->get_points()) {
            if(collides(p.x, p.y))
                return true;
        }
    }
    return false;
}

void Rectangle::calculatePoints() {
    _points[0] = {_x, _y};
    _points[1] = {_x + _width, _y};
    _points[2] = {_x, _y + _height};
    _points[3] = {_x + _width, _y + _height};
}

double Rectangle::get_center_x() {
    return _x + 0.5*_width;
}

double Rectangle::get_center_y() {
    return _y + 0.5*_height;
}
