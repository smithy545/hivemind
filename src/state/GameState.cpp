//
// Created by smith on 3/23/2020.
//

#include "GameState.h"


GameState::GameState() : camera(nullptr) {
    for (bool &key : keys)
        key = false;
}

std::vector<SchemaPrototype::Ptr> GameState::getEntities() {
    return entities;
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

void GameState::addSchemaEntity(const SchemaPrototype::Ptr &entity) {
    entities.push_back(entity);
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
