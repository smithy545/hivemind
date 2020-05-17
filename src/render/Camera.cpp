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
    scale *= 0.9;
    resetProjectionMatrix();
}

void Camera::zoomOut() {
    scale *= 1.1;
    resetProjectionMatrix();
}

void Camera::resize(double width, double height) {
    bound.setWidth(width);
    bound.setHeight(height);
    resetProjectionMatrix();
}

#include <iostream>
void Camera::resetProjectionMatrix() {
    projectionMatrix = glm::ortho(0.f, (float) (scale * bound.getWidth()), 0.f, (float) (scale * bound.getHeight()));
}

void Camera::resetViewMatrix() {
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
