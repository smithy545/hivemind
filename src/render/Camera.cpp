//
// Created by Philip on 2/8/2020.
//

#include "Camera.h"

#include <glm/ext.hpp>
#include <glm/gtx/rotate_vector.hpp>


Camera::Camera(double width, double height)
        : _bounding_rect(0, 0, width, height) {
    reset_projection_matrix();
    reset_view_matrix();
}

void Camera::pan_left() {
    _forward = glm::rotate(_forward, horizontal_rotation_speed, _up);
    reset_view_matrix();
}

void Camera::pan_right() {
    _forward = glm::rotate(_forward, -horizontal_rotation_speed, _up);
    reset_view_matrix();
}

void Camera::pan_up() {
    auto left = glm::cross(_up, _forward);
    _forward = glm::rotate(_forward, -vertical_rotation_speed, left);
    _up = glm::rotate(_up, -vertical_rotation_speed, left);
    reset_view_matrix();
}

void Camera::pan_down() {
    auto left = glm::cross(_up, _forward);
    _forward = glm::rotate(_forward, vertical_rotation_speed, left);
    _up = glm::rotate(_up, vertical_rotation_speed, left);
    reset_view_matrix();
}

void Camera::pan_horizontal(float speed) {
    _forward = glm::rotate(_forward, speed, -_up);
    reset_view_matrix();
}

void Camera::pan_vertical(float speed) {
    auto left = glm::cross(_up, _forward);
    _forward = glm::rotate(_forward, speed, left);
    _up = glm::rotate(_up, speed, left);
    reset_view_matrix();
}

void Camera::move(glm::vec3 differential) {
    _position += differential;
    reset_view_matrix();
}

void Camera::move_forward() {
    _position += translation_speed * _forward;
    reset_view_matrix();
}

void Camera::move_backword() {
    _position -= translation_speed * _forward;
    reset_view_matrix();
}

void Camera::move_up() {
    _position += translation_speed * _up;
    reset_view_matrix();
}

void Camera::move_down() {
    _position -= translation_speed * _up;
    reset_view_matrix();
}

void Camera::strafe_left() {
    _position += translation_speed * glm::cross(_up, _forward);
    reset_view_matrix();
}

void Camera::strafe_right() {
    _position -= translation_speed * glm::cross(_up, _forward);
    reset_view_matrix();
}

// TODO: Zoom
void Camera::zoom_in() {}
void Camera::zoom_out() {}

void Camera::resize(float width, float height) {
    _bounding_rect.set_width(width);
    _bounding_rect.set_height(height);
    reset_projection_matrix();
}

void Camera::reset_projection_matrix() {
    float aspect = _bounding_rect.get_width() / _bounding_rect.get_height();
    projection_matrix = glm::perspective(glm::radians(90.0f), aspect, 0.1f, 100.0f);
}

void Camera::reset_view_matrix() {
    _bounding_rect.set_x(_position.x);
    _bounding_rect.set_y(_position.y);
    view_matrix = glm::lookAt(_position, _position + _forward, _up);
}

glm::mat4 Camera::get_view_projection_matrix() const {
    return projection_matrix * view_matrix;
}

bool Camera::is_visible(glm::vec3 point) {
    // TODO: improve from rough sphere culling
    return glm::length(point - _position) < 100.0f;
}