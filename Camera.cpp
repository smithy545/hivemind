//
// Created by Philip on 2/8/2020.
//

#include "Camera.h"

Camera::Camera(double x, double y, double width, double height) : x(x), y(y), width(width), height(height) {}

bool Camera::inSight(const MapNode::Ptr &node) {
    // TODO: Improve to include node size
    return node->x >= x && node->x < x + width && node->y >= y && node->y < y + height;
}