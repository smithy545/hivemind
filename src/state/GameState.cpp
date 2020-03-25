//
// Created by smith on 3/23/2020.
//

#include "GameState.h"


GameState::GameState() {
    for (int i = 0; i < GLFW_KEY_LAST; i++)
        keys[i] = false;
}

std::vector<SchemaEntity::Ptr> GameState::getEntities() {
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

void GameState::add(SchemaEntity::Ptr entity) {
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
