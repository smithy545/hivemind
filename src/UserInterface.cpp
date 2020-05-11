//
// Created by Philip on 2/25/2020.
//

#include "UserInterface.h"

#include <iostream>
#include <exception>
#include <fmt/format.h>
#include <pathing/Pather.h>
#include <util/FileUtil.h>


UserInterface::UserInterface(const std::string &configPath) {
    json config = FileUtil::readJsonFile(configPath);
    for (const auto &component: config["components"].items()) {
        json schema;
        if (component.value().is_string())
            schema = FileUtil::readJsonFile(component.value());
        else if (component.value().is_object())
            schema = component.value();
        else
            throw std::exception("Error reading ui config from ");

        components[component.key()] = std::make_shared<SchemaObject>(schema);
    }
}

void UserInterface::update(const GameState::Ptr &state) {
    // update camera
    if (state->getMouseScroll() > 0) {
        //state->getCamera()->zoomIn();

        tileId = (tileId + 1) % (32 * 32);
    } else if (state->getMouseScroll() < 0) {
        //state->getCamera()->zoomOut();

        tileId = (tileId - 1) >= 0 ? (tileId - 1) : (32 * 32 - 1);
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

void UserInterface::addComponentAt(int x, int y, const std::string &componentType) {
    if (components.find(componentType) == components.end()) {
        std::cerr << "Could not add SchemaEntity nonexistent ui component " << componentType << std::endl;
    } else {
        json obj = {{"x",      x},
                    {"y",      y},
                    {"sprite", componentType}};
        //components[componentType]->generate(obj);
    }
}

const std::unordered_map<std::string, SchemaObject::Ptr> &UserInterface::getComponents() const {
    return components;
}
