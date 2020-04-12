//
// Created by smith on 3/23/2020.
//

#include "GameState.h"


GameState::GameState() : camera(nullptr) {
    map = std::make_shared<WorldMap>();
    for (bool &key : keys)
        key = false;
}

const std::vector<WorldEntity::Ptr> &GameState::getWorldEntities() const {
    return worldEntities;
}

const std::vector<UIEntity::Ptr> &GameState::getUiEntities() const {
    return uiEntities;
}

bool GameState::getKey(int key) const {
    return keys[key];
}

double GameState::getMouseX() const {
    return mouseX;
}

double GameState::getMouseY() const {
    return mouseY;
}

double GameState::getMouseScroll() const {
    return mouseScroll;
}

void GameState::setKey(int key, bool value) {
    keys[key] = value;
}

void GameState::setMouseX(double mouseX) {
    this->mouseX = mouseX;
}

void GameState::setMouseY(double mouseY) {
    this->mouseY = mouseY;
}

void GameState::setMouseScroll(double mouseScroll) {
    this->mouseScroll = mouseScroll;
}

Camera::Ptr &GameState::getCamera() {
    return camera;
}

void GameState::setCamera(const Camera::Ptr &camera) {
    GameState::camera = camera;
}

const WorldMap::Ptr &GameState::getMap() const {
    return map;
}

void GameState::setMap(const WorldMap::Ptr &map) {
    GameState::map = map;
}
