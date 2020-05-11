//
// Created by smith on 3/23/2020.
//

#include "GameState.h"


GameState::GameState() : camera(nullptr), map(nullptr) {
    for (bool &key : keys)
        key = false;
}

RenderNode::Ptr GameState::getRenderTree() {
    auto temp = std::make_shared<RenderNode>("gorilla");
    temp->addChild(100, 100, 1);
    return temp;
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

const Map::Ptr &GameState::getMap() const {
    return map;
}

void GameState::setMap(const Map::Ptr &map) {
    GameState::map = map;
}

bool GameState::isPaused() const {
    return paused;
}

bool GameState::shouldStop() const {
    return stopped;
}

void GameState::pause() {
    paused = true;
}

void GameState::unpause() {
    paused = false;
}

void GameState::start() {
    paused = false;
    stopped = false;
}

void GameState::stop() {
    stopped = true;
    lastFrameStart = std::chrono::system_clock::now();
}

void GameState::enterFrame() {
    auto currentFrame = std::chrono::system_clock::now();
    fps = 1.0 / std::chrono::duration<double>(currentFrame - lastFrameStart).count();
    lastFrameStart = currentFrame;
}

double GameState::getFPS() const {
    return fps;
}

