//
// Created by Philip on 2/25/2020.
//

#include "UserInterface.h"

#include <utility>
#include <src/pathing/Pather.h>


UserInterface::UserInterface(GridMap::Ptr map) : map(std::move(map)) {}

void UserInterface::update(float mouseX, float mouseY, Renderer::Ptr renderer) {
    // move adam to mouse pointer
    auto adam = map->getActors()[0];
    int mx = mouseX / (1. * renderer->getTileSize());
    int my = (renderer->getHeight() - mouseY) / (1. * renderer->getTileSize());
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


