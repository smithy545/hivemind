//
// Created by Philip on 2/8/2020.
//

#include "Camera.h"

Camera::Camera(double x, double y, double width, double height) : x(x), y(y), width(width), height(height) {}

bool Camera::inSight(const MapNode::Ptr &node) const {
    // TODO: Improve to include node size
    return node->getX() >= x
           && node->getX() < x + width
           && node->getY() >= y
           && node->getY() < y + height;
}

double Camera::getX() const {
    return x;
}

void Camera::setX(double x) {
    Camera::x = x;
}

double Camera::getY() const {
    return y;
}

void Camera::setY(double y) {
    Camera::y = y;
}

double Camera::getWidth() const {
    return width;
}

void Camera::setWidth(double width) {
    Camera::width = width;
}

double Camera::getHeight() const {
    return height;
}

void Camera::setHeight(double height) {
    Camera::height = height;
}
