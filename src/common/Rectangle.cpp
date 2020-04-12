//
// Created by smith on 4/12/2020.
//

#include "Rectangle.h"


Rectangle::Rectangle(float width, float height) : Rectangle(0, 0, width, height) {}

Rectangle::Rectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {
    calculatePoints();
}

bool Rectangle::collides(float X, float Y) {
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

float Rectangle::getX() const {
    return x;
}

void Rectangle::setX(float x) {
    Rectangle::x = x;
    calculatePoints();
}

float Rectangle::getY() const {
    return y;
}

void Rectangle::setY(float y) {
    Rectangle::y = y;
    calculatePoints();
}

float Rectangle::getWidth() const {
    return width;
}

void Rectangle::setWidth(float width) {
    Rectangle::width = width;
    calculatePoints();
}

float Rectangle::getHeight() const {
    return height;
}

void Rectangle::setHeight(float height) {
    Rectangle::height = height;
    calculatePoints();
}

const float *Rectangle::getPoints() const {
    return points;
}
