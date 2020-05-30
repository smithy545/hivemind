//
// Created by Philip on 2/8/2020.
//

#include "Camera.h"

#include <glm/ext.hpp>


Camera::Camera(double x, double y, double width, double height)
        : pos(x, y, 0), bound(x, y, width, height) {
    resetProjectionMatrix();
    resetViewMatrix();
}

bool Camera::inSight(double x, double y) {
    return bound.collides(x, y);
}

bool Camera::inSight(glm::vec2 pos) {
    return bound.collides(pos.x, pos.y);
}

bool Camera::inSight(Rectangle obj) {
    return bound.collides(obj);
}

void Camera::panLeft() {
    pos.x -= scale;
    resetViewMatrix();
}

void Camera::panRight() {
    pos.x += scale;
    resetViewMatrix();
}

void Camera::panUp() {
    pos.y += scale;
    resetViewMatrix();
}

void Camera::panDown() {
    pos.y -= scale;
    resetViewMatrix();
}

void Camera::zoomIn() {
    scale *= 0.5;
    resetProjectionMatrix();
}

void Camera::zoomOut() {
    scale *= 2.0;
    resetProjectionMatrix();
}

void Camera::resize(double width, double height) {
    resetProjectionMatrix();
}

void Camera::resetProjectionMatrix() {
    float width = scale * bound.getWidth();
    float height = scale * bound.getHeight();
    bound.setWidth(width);
    bound.setHeight(height);
    projectionMatrix = glm::ortho(0.f, width, 0.f, height);
}

void Camera::resetViewMatrix() {
    bound.setX(pos.x);
    bound.setY(pos.y);
    viewMatrix = glm::translate(glm::mat4(1), -pos);
}

glm::mat4 Camera::getViewProjectionMatrix() {
    return projectionMatrix * viewMatrix;
}

Rectangle Camera::getBoundingRect() {
    return bound;
}

double Camera::getScale() const {
    return scale;
}
