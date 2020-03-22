//
// Created by Philip on 2/25/2020.
//

#include "UserInterface.h"

#include <memory>
#include <utility>

#include "pathing/Pather.h"
#include "world/Human.h"


UserInterface::UserInterface(GridMap::Ptr map) : map(std::move(map)) {}

void UserInterface::update(const bool keys[GLFW_KEY_LAST],
                           float mouseX,
                           float mouseY,
                           float mouseScroll,
                           const Camera::Ptr &camera,
                           int tilesize) {
    // update camera
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

    if (mouseX >= 0 && mouseY >= 0) {
        // load mouse tile
        float scale = camera->getScale();
        int mx = (camera->getX() + scale * mouseX) / tilesize;
        int my = (camera->getY() + scale * (camera->getHeight() - mouseY)) / tilesize;
        int gridWidth = map->getWidth();
        int gridHeight = map->getHeight();
        int gridX = mx < gridWidth ? mx : gridWidth - 1;
        int gridY = my < gridHeight ? my : gridHeight - 1;
        auto node = map->getNode(gridX, gridY);

        if (node == nullptr || map->getActors().empty())
            return;

        // move adam (first man) to mouse pointer
        auto adam = map->getActors()[0];
        if ((gridX != adam->getX() || gridY != adam->getY()) && adam->getPath().empty()) {
            MapNode::MapPath path = Pather::genAStarPath(adam->getPosition(), node);
            for (const auto &step: path) {
                adam->addToPath(step);
            }
        }
    }
}

const std::vector<UIEntity::Ptr> &UserInterface::getEntities() const {
    return entities;
}
