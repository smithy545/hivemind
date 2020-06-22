//
// Created by Philip on 2/8/2020.
//

#include "Camera.h"

#include <glm/ext.hpp>
#include <glm/gtx/rotate_vector.hpp>


Camera::Camera(double width, double height)
        : _bounding_rect(0, 0, width, height) {
    resetProjectionMatrix();
    resetViewMatrix();
}

void Camera::panLeft() {
    _forward = glm::rotate(_forward, horizontalRotationSpeed, _up);
    resetViewMatrix();
}

void Camera::panRight() {
    _forward = glm::rotate(_forward, -horizontalRotationSpeed, _up);
    resetViewMatrix();
}

void Camera::panUp() {
    auto left = glm::cross(_up, _forward);
    _forward = glm::rotate(_forward, -verticalRotationSpeed, left);
    _up = glm::rotate(_up, -verticalRotationSpeed, left);
    resetViewMatrix();
}

void Camera::panDown() {
    auto left = glm::cross(_up, _forward);
    _forward = glm::rotate(_forward, verticalRotationSpeed, left);
    _up = glm::rotate(_up, verticalRotationSpeed, left);
    resetViewMatrix();
}

void Camera::panHorizontal(float speed) {
    _forward = glm::rotate(_forward, speed, -_up);
    resetViewMatrix();
}

void Camera::panVertical(float speed) {
    auto left = glm::cross(_up, _forward);
    _forward = glm::rotate(_forward, speed, left);
    _up = glm::rotate(_up, speed, left);
    resetViewMatrix();
}

void Camera::move(glm::vec3 differential) {
    _position += differential;
    resetViewMatrix();
}

void Camera::moveForward() {
    _position += translationSpeed*_forward;
    resetViewMatrix();
}

void Camera::moveBackword() {
    _position -= translationSpeed*_forward;
    resetViewMatrix();
}

void Camera::moveUp() {
    _position += translationSpeed*_up;
    resetViewMatrix();
}

void Camera::moveDown() {
    _position -= translationSpeed*_up;
    resetViewMatrix();
}

void Camera::strafeLeft() {
    _position += translationSpeed*glm::cross(_up, _forward);
    resetViewMatrix();
}

void Camera::strafeRight() {
    _position -= translationSpeed*glm::cross(_up, _forward);
    resetViewMatrix();
}

void Camera::setPosition(const glm::vec3 &position) {
    _position = position;
    resetViewMatrix();
}

// TODO: Zoom
void Camera::zoomIn() {}
void Camera::zoomOut() {}

void Camera::resize(float width, float height) {
    _bounding_rect.set_width(width);
    _bounding_rect.set_height(height);
    resetProjectionMatrix();
}

void Camera::resetProjectionMatrix() {
    float width = _bounding_rect.get_width();
    float height = _bounding_rect.get_height();
    projectionMatrix = glm::perspective(glm::radians(90.0f), width/height, 0.1f, 100.0f);
}

void Camera::resetViewMatrix() {
    _bounding_rect.set_x(_position.x);
    _bounding_rect.set_y(_position.y);
    viewMatrix = glm::lookAt(_position, _position + _forward, _up);
}

glm::mat4 Camera::getViewProjectionMatrix() const {
    return projectionMatrix * viewMatrix;
}
