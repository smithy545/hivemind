//
// Created by Philip on 2/8/2020.
//

#include "Camera.h"

#include <glm/ext.hpp>


Camera::Camera(float x, float y, float width, float height, float tileSize)
        : pos(x, y), width(width), scale(1), height(height), tileSize(tileSize),
          viewMatrix(glm::translate(glm::mat4(1), glm::vec3(-pos, 0))),
          projectionMatrix(glm::ortho(0.f, width, 0.f, height, -1.f, 1.f)) {}

bool Camera::inSight(const MapNode::Ptr &node) const {
    // TODO: Improve to include node size
    return (node->getX() + 1) * tileSize > pos.x
           && node->getX() * tileSize < pos.x + scale * width
           && (node->getY() + 1) * tileSize > pos.y
           && node->getY() * tileSize < pos.y + scale * height;
}

void Camera::panLeft() {
    pos.x -= scale;
    viewMatrix = glm::translate(glm::mat4(1), glm::vec3(-pos, 0));
}

void Camera::panRight() {
    pos.x += scale;
    viewMatrix = glm::translate(glm::mat4(1), glm::vec3(-pos, 0));
}

void Camera::panUp() {
    pos.y += scale;
    viewMatrix = glm::translate(glm::mat4(1), glm::vec3(-pos, 0));
}

void Camera::panDown() {
    pos.y -= scale;
    viewMatrix = glm::translate(glm::mat4(1), glm::vec3(-pos, 0));
}

void Camera::zoomIn() {
    scale *= 0.9;
    projectionMatrix = glm::ortho(0.f, scale * width, 0.f, scale * height, -1.f, 1.f);
}

void Camera::zoomOut() {
    scale *= 1.1;
    projectionMatrix = glm::ortho(0.f, scale * width, 0.f, scale * height, -1.f, 1.f);
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

void Camera::setWidth(float width) {
    this->width = width;
}

float Camera::getHeight() const {
    return height;
}

void Camera::setHeight(float height) {
    this->height = height;
}

float Camera::getTileSize() const {
    return tileSize;
}

void Camera::setTileSize(double tileSize) {
    this->tileSize = tileSize;
}

float Camera::getScale() const {
    return scale;
}
