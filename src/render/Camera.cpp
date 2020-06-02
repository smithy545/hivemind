//
// Created by Philip on 2/8/2020.
//

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/rotate_vector.hpp>


Camera::Camera(double width, double height)
        : bound(0, 0, width, height) {
    resetProjectionMatrix();
    resetViewMatrix();
}

bool Camera::inSight(double x, double y, double z) {
    return bound.collides(x, y);
}

bool Camera::inSight(glm::vec3 pos) {
    return bound.collides(pos.x, pos.y);
}

bool Camera::inSight(const Rectangle& obj) {
    return bound.collides(std::make_shared<Rectangle>(obj));
}

void Camera::panLeft() {
    forward = glm::rotate(forward, scale, up);
    resetViewMatrix();
}

void Camera::panRight() {
    forward = glm::rotate(forward, -scale, up);
    resetViewMatrix();
}

void Camera::panUp() {
    auto left = glm::cross(up, forward);
    forward = glm::rotate(forward, -scale, left);
    up = glm::rotate(up, -scale, left);
    resetViewMatrix();
}

void Camera::panDown() {
    auto left = glm::cross(up, forward);
    forward = glm::rotate(forward, scale, left);
    up = glm::rotate(up, scale, left);
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
    float width = bound.getWidth();
    float height = bound.getHeight();
    bound.setWidth(width);
    bound.setHeight(height);
    projectionMatrix = glm::perspective(glm::radians(90.0f), width/height, 0.1f, 100.0f);
}

void Camera::resetViewMatrix() {
    bound.setX(position.x);
    bound.setY(position.y);
    viewMatrix = glm::lookAt(position, position + forward, up);
}

const glm::mat4 Camera::getViewProjectionMatrix() const {
    return projectionMatrix * viewMatrix;
}

Rectangle Camera::getBoundingRect() {
    return bound;
}

float Camera::getScale() const {
    return scale;
}

void Camera::moveForward() {
    position += scale*forward;
    resetViewMatrix();
}

void Camera::moveBackword() {
    position -= scale*forward;
    resetViewMatrix();
}

void Camera::moveLeft() {
    position += scale*glm::cross(up, forward);
    resetViewMatrix();
}

void Camera::moveRight() {
    position -= scale*glm::cross(up, forward);
    resetViewMatrix();
}

void Camera::moveUp() {
    position += scale*up;
    resetViewMatrix();
}

void Camera::moveDown() {
    position -= scale*up;
    resetViewMatrix();
}
