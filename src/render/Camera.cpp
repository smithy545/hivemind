//
// Created by Philip on 2/8/2020.
//

#include "Camera.h"

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
    forward = glm::rotate(forward, horizontalRotationSpeed, up);
    resetViewMatrix();
}

void Camera::panRight() {
    forward = glm::rotate(forward, -horizontalRotationSpeed, up);
    resetViewMatrix();
}

void Camera::panUp() {
    auto left = glm::cross(up, forward);
    forward = glm::rotate(forward, -verticalRotationSpeed, left);
    up = glm::rotate(up, -verticalRotationSpeed, left);
    resetViewMatrix();
}

void Camera::panDown() {
    auto left = glm::cross(up, forward);
    forward = glm::rotate(forward, verticalRotationSpeed, left);
    up = glm::rotate(up, verticalRotationSpeed, left);
    resetViewMatrix();
}

// TODO: Zoom
void Camera::zoomIn() {}
void Camera::zoomOut() {}


void Camera::resize(double width, double height) {
    resetProjectionMatrix();
}

void Camera::resetProjectionMatrix() {
    float width = bound.getWidth();
    float height = bound.getHeight();
    projectionMatrix = glm::perspective(glm::radians(90.0f), width/height, 0.1f, 100.0f);
}

void Camera::resetViewMatrix() {
    bound.setX(position.x);
    bound.setY(position.y);
    viewMatrix = glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::getViewProjectionMatrix() const {
    return projectionMatrix * viewMatrix;
}

Rectangle Camera::getBoundingRect() {
    return bound;
}

void Camera::moveForward() {
    position += translationSpeed*forward;
    resetViewMatrix();
}

void Camera::moveBackword() {
    position -= translationSpeed*forward;
    resetViewMatrix();
}

void Camera::strafeLeft() {
    position += translationSpeed*glm::cross(up, forward);
    resetViewMatrix();
}

void Camera::strafeRight() {
    position -= translationSpeed*glm::cross(up, forward);
    resetViewMatrix();
}

void Camera::moveUp() {
    position += translationSpeed*up;
    resetViewMatrix();
}

void Camera::moveDown() {
    position -= translationSpeed*up;
    resetViewMatrix();
}
