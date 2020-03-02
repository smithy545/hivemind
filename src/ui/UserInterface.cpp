//
// Created by Philip on 2/25/2020.
//

#include "UserInterface.h"

#include <iostream>
#include <utility>
#include <src/pathing/Pather.h>


UserInterface::UserInterface(GridMap::Ptr map) : map(std::move(map)) {}

void UserInterface::update(const bool keys[GLFW_KEY_LAST], float mouseX, float mouseY, float mouseScroll,
                           const Renderer::Ptr &renderer) {
    // update camera
    Camera::Ptr camera = renderer->getCamera();
    if (mouseScroll > 0) {
        camera->zoomIn();
    } else if (mouseScroll < 0) {
        camera->zoomOut();
    }
    if (keys[GLFW_KEY_LEFT]) {
        camera->panLeft();
    }
    if (keys[GLFW_KEY_RIGHT]) {
        camera->panRight();
    }
    if (keys[GLFW_KEY_UP]) {
        camera->panUp();
    }
    if (keys[GLFW_KEY_DOWN]) {
        camera->panDown();
    }

    if (map->getActors().empty())
        return;

    // move adam to mouse pointer
    auto adam = map->getActors()[0];
    float scale = camera->getScale();
    int mx = (renderer->getCamera()->getX() + scale * mouseX) / renderer->getTileSize();
    int my = (renderer->getCamera()->getY() + scale * (renderer->getHeight() - mouseY)) / renderer->getTileSize();
    int gridWidth = map->getWidth();
    int gridHeight = map->getHeight();
    int gridX = mx < gridWidth ? mx : gridWidth - 1;
    int gridY = my < gridHeight ? my : gridHeight - 1;
    auto node = map->getNode(gridX, gridY);
    if (node != nullptr
        && (gridX != adam->getPosition()->getX() || gridY != adam->getPosition()->getY())
        && adam->getPath().empty()) {
        MapNode::MapPath path = Pather::genAStarPath(adam->getPosition(), node);
        for (const auto &step: path) {
            adam->addToPath(step);
        }
    }
}


