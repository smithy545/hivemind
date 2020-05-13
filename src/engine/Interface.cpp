//
// Created by Philip on 2/25/2020.
//

#include "Interface.h"

#include <exception>
#include <util/FileUtil.h>


Interface::Interface(const std::string &configPath) {
    json config = FileUtil::readJsonFile(configPath);
    // DOES NOTHING BUT READ THE FILE RIGHT NOW
    for (const auto &component: config["components"].items()) {
        json schema;
        if (component.value().is_string())
            schema = FileUtil::readJsonFile(component.value());
        else if (component.value().is_object())
            schema = component.value();
        else
            throw std::exception("Error reading ui config from ");
    }
}

void Interface::update(const State::Ptr &state) {
    if (state->getMouseScroll() > 0) {
        state->getCamera()->zoomIn();
    } else if (state->getMouseScroll() < 0) {
        state->getCamera()->zoomOut();
    }
    if (state->getKey(GLFW_KEY_LEFT)) {
        state->getCamera()->panLeft();
    }
    if (state->getKey(GLFW_KEY_RIGHT)) {
        state->getCamera()->panRight();
    }
    if (state->getKey(GLFW_KEY_UP)) {
        state->getCamera()->panUp();
    }
    if (state->getKey(GLFW_KEY_DOWN)) {
        state->getCamera()->panDown();
    }


    if (state->getMouseX() >= 0 && state->getMouseY() >= 0) {
        // load mouse tile
        /*
         *         addComponentAt(0, 0, "EntityInfoBox");

        float scale = camera->getScale();
        int mx = (camera->getX() + scale * mouseX) / tileSize;
        int my = (camera->getY() + scale * (camera->getHeight() - mouseY)) / tileSize;
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
         */
    }
}
