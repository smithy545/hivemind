//
// Created by Philip on 2/25/2020.
//

#include "UserInterface.h"

#include <iostream>
#include <utility>
#include <src/pathing/Pather.h>


UserInterface::UserInterface(GridMap::Ptr map) : map(std::move(map)) {}

void UserInterface::update(const bool keys[GLFW_KEY_LAST], float mouseX, float mouseY, const Renderer::Ptr &renderer) {
    // update camera
    if (keys[GLFW_KEY_LEFT]) {
        renderer->getCamera()->panLeft();
    }
    if (keys[GLFW_KEY_RIGHT]) {
        renderer->getCamera()->panRight();
    }
    if (keys[GLFW_KEY_UP]) {
        renderer->getCamera()->panUp();
    }
    if (keys[GLFW_KEY_DOWN]) {
        renderer->getCamera()->panDown();
    }

    // move adam to mouse pointer
    auto adam = map->getActors()[0];
    int mx = (mouseX - renderer->getCamera()->getX()) / (1. * renderer->getTileSize());
    int my = (renderer->getHeight() - mouseY - renderer->getCamera()->getY()) / (1. * renderer->getTileSize());
    int gridWidth = map->getWidth();
    int gridHeight = map->getHeight();
    int gridX = mx < gridWidth ? mx : gridWidth - 1;
    int gridY = my < gridHeight ? my : gridHeight - 1;
    if ((gridX != adam->getPosition()->getX() || gridY != adam->getPosition()->getY()) && adam->getPath().empty()) {
        MapNode::MapPath path = Pather::genAStarPath(adam->getPosition(),
                                                     map->getNode(gridX, gridY));
        for (const auto &step: path) {
            adam->addToPath(step);
        }
    }
}


