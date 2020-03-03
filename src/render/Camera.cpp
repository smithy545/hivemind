//
// Created by Philip on 2/8/2020.
//

#include "Camera.h"

#include <glm/ext.hpp>


Camera::Camera(float x, float y, float width, float height, float tileSize)
        : pos(x, y), width(width), scale(1), height(height), tileSize(tileSize) {
    resetProjectionMatrix();
    resetViewMatrix();
}

bool Camera::inSight(const MapNode::Ptr &node) const {
    // TODO: Improve to include node size
    return (node->getX() + 1) * tileSize > pos.x
           && node->getX() * tileSize < pos.x + scale * width
           && (node->getY() + 1) * tileSize > pos.y
           && node->getY() * tileSize < pos.y + scale * height;
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

void Camera::resize(int width, int height) {
    this->width = width;
    this->height = height;
    resetProjectionMatrix();
}

void Camera::setTileSize(double tileSize) {
    this->tileSize = tileSize;
}

void Camera::resetProjectionMatrix() {
    projectionMatrix = glm::ortho(0.f, scale * width, 0.f, scale * height);
}

void Camera::resetViewMatrix() {
    viewMatrix = glm::translate(glm::mat4(1), glm::vec3(-pos, 0));
}

glm::mat4 Camera::getViewProjectionMatrix() {
    return projectionMatrix * viewMatrix;
}

float Camera::getX() const {
    return pos.x;
}

float Camera::getY() const {
    return pos.y;
}

float Camera::getWidth() const {
    return width;
}

float Camera::getHeight() const {
    return height;
}

float Camera::getTileSize() const {
    return tileSize;
}

float Camera::getScale() const {
    return scale;
}
