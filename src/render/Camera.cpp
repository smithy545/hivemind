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

void Camera::panHorizontal(float speed) {
    forward = glm::rotate(forward, speed, -up);
    resetViewMatrix();
}

void Camera::panVertical(float speed) {
    auto left = glm::cross(up, forward);
    forward = glm::rotate(forward, speed, left);
    up = glm::rotate(up, speed, left);
    resetViewMatrix();
}

void Camera::moveForward() {
    position += translationSpeed*forward;
    resetViewMatrix();
}

void Camera::moveBackword() {
    position -= translationSpeed*forward;
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

void Camera::strafeLeft() {
    position += translationSpeed*glm::cross(up, forward);
    resetViewMatrix();
}

void Camera::strafeRight() {
    position -= translationSpeed*glm::cross(up, forward);
    resetViewMatrix();
}

// TODO: Zoom
void Camera::zoomIn() {}
void Camera::zoomOut() {}

void Camera::resize(float width, float height) {
    bound.setWidth(width);
    bound.setHeight(height);
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