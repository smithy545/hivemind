//
// Created by smith on 4/12/2020.
//

#include "Rectangle.h"


Rectangle::Rectangle(double width, double height) : Rectangle(0, 0, width, height) {}

Rectangle::Rectangle(double x, double y, double width, double height) : x(x), y(y),
                                                                        centerX(x - 0.5 * width),
                                                                        centerY(y - 0.5 * height),
                                                                        width(width), height(height) {
    calculatePoints();
}

bool Rectangle::collides(double X, double Y) const {
    return X >= x && X < x + width && Y >= y && Y < y + height;
}

bool Rectangle::collides(Bound::Ptr other) {
    auto rect = std::dynamic_pointer_cast<Rectangle>(other);
    if(rect != nullptr) {
        if(other->collides(this->shared_from_this()))
            return true;
        auto otherPoints = rect->getPoints();
        for (auto p: otherPoints) {
            if(collides(p.x, p.y))
                return true;
        }
    }
    return false;
}

void Rectangle::calculatePoints() {
    points[0] = {x, y};
    points[1] = {x + width, y};
    points[2] = {x, y + height};
    points[3] = {x + width, y + height};
}

double Rectangle::getX() const {
    return x;
}

void Rectangle::setX(double x) {
    Rectangle::x = x;
    calculatePoints();
}

double Rectangle::getY() const {
    return y;
}

void Rectangle::setY(double y) {
    Rectangle::y = y;
    calculatePoints();
}

double Rectangle::getWidth() const {
    return width;
}

void Rectangle::setWidth(double width) {
    Rectangle::width = width;
    calculatePoints();
}

double Rectangle::getHeight() const {
    return height;
}

void Rectangle::setHeight(double height) {
    Rectangle::height = height;
    calculatePoints();
}

std::vector<glm::vec2> Rectangle::getPoints() {
    return points;
}

double Rectangle::getCenterX() const {
    return centerX;
}

void Rectangle::setCenterX(double centerX) {
    Rectangle::centerX = centerX;
    Rectangle::x = centerX - width * 0.5;
    calculatePoints();
}

double Rectangle::getCenterY() const {
    return centerY;
}

void Rectangle::setCenterY(double centerY) {
    Rectangle::centerY = centerY;
    Rectangle::y = centerY - height * 0.5;
    calculatePoints();
}
