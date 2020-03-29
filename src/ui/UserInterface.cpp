//
// Created by Philip on 2/25/2020.
//

#include "UserInterface.h"

#include <exception>
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

        components[component.key()] = std::make_shared<SchemaEntity>(schema);
    }
}

void UserInterface::update(const GameState::Ptr &state) {
    // update camera
    if (state->getMouseScroll() > 0) {
        //camera->zoomIn();
    } else if (state->getMouseScroll() < 0) {
        //camera->zoomOut();
    }
    if (state->getKey(GLFW_KEY_LEFT)) {
        //camera->panLeft();
    }
    if (state->getKey(GLFW_KEY_RIGHT)) {
        //camera->panRight();
    }
    if (state->getKey(GLFW_KEY_UP)) {
        //camera->panUp();
    }
    if (state->getKey(GLFW_KEY_DOWN)) {
        //camera->panDown();
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

void UserInterface::addComponentAt(int x, int y, const std::string &component) {
    if (components.find(component) == components.end()) {
        std::cerr << "Could not addSchemaEntity nonexistent ui component " << component << std::endl;
    } else {
        components[component]->generate({{"x",      x},
                                         {"y",      y},
                                         {"sprite", "gorilla"}});
    }
}

const std::unordered_map<std::string, SchemaEntity::Ptr> &UserInterface::getComponents() const {
    return components;
}

std::vector<SchemaEntity::Ptr> UserInterface::getComponentEntities() {
    std::vector<SchemaEntity::Ptr> entities;
    for (const auto &pair: components)
        entities.push_back(pair.second);
    return entities;
}
