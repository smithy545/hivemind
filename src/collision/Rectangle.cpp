//
// Created by smith on 4/12/2020.
//

#include "Rectangle.h"


Rectangle::Rectangle(double width, double height) : Rectangle(0, 0, width, height) {}

Rectangle::Rectangle(double x, double y, double width, double height) : x(x), y(y), width(width), height(height) {
    calculatePoints();
}

bool Rectangle::collides(double X, double Y) const {
    return X >= x && X < x + width && Y >= y && Y < y + height;
}

bool Rectangle::collides(Rectangle rect) {
    for (int i = 0; i < 8; i += 2)
        if (rect.collides(points[i], points[i + 1]))
            return true;
    return false;
}

void Rectangle::calculatePoints() {
    points[0] = x;
    points[1] = y;
    points[2] = x + width;
    points[3] = y;
    points[4] = x;
    points[5] = y + height;
    points[6] = x + width;
    points[7] = y + height;
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

const double *Rectangle::getPoints() const {
    return points;
}
