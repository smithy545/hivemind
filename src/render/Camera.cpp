//
// Created by Philip on 2/8/2020.
//

#include "Camera.h"

Camera::Camera(double x, double y, double width, double height, double tileSize) : x(x), y(y), width(width),
                                                                                   height(height), tileSize(tileSize) {}

bool Camera::inSight(const MapNode::Ptr &node) const {
    // TODO: Improve to include node size
    return (node->getX() + 1) * tileSize > x
           && node->getX() * tileSize < x + width
           && (node->getY() + 1) * tileSize > y
           && node->getY() * tileSize < y + height;
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

double Camera::getTileSize() const {
    return tileSize;
}

void Camera::setTileSize(double tileSize) {
    Camera::tileSize = tileSize;
}