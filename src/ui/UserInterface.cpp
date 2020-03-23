//
// Created by Philip on 2/25/2020.
//

#include "UserInterface.h"

#include <pathing/Pather.h>
#include <util/FileUtil.h>


UserInterface::UserInterface(const std::string &configPath) {
    json config = FileUtil::readJsonFile(configPath);
    for (const auto &component: config["components"].items()) {
        if (component.value().is_string()) {
            json schema = FileUtil::readJsonFile(component.value());
            availableComponents[component.key()] = std::make_shared<UIEntity>(schema);
        } else if (component.value().is_object()) {
            availableComponents[component.key()] = std::make_shared<UIEntity>(component.value());
        }
    }
}

void UserInterface::update(GameState::Ptr state) {
    // update camera
    /*
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
    }
     */
}

void UserInterface::add(int x, int y, const std::string &component) {
    if (availableComponents.find(component) == availableComponents.end()) {
        std::cerr << "Could not add nonexistent ui component " << component << std::endl;
    } else {
        auto entity = std::make_shared<UIEntity>(component);
        loadedEntities.push_back(entity);
    }
}

const std::vector<UIEntity::Ptr> &UserInterface::getEntities() const {
    return loadedEntities;
}

