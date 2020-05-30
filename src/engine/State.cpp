//
// Created by smith on 3/23/2020.
//

#include "State.h"

#include <fmt/format.h>


State::State() : camera(nullptr), head(nullptr), map(nullptr) {
    for (bool &key : keys)
        key = false;
    head = std::make_shared<RenderNode>("nude", "texture");
    head->addChild({0,0,16,16});
}

RenderNode::Ptr State::getRenderTree() {
    if (map == nullptr)
        return nullptr;

    return head;
}

bool State::getKey(int key) const {
    return keys[key];
}

double State::getMouseX() const {
    return mouseX;
}

double State::getMouseY() const {
    return mouseY;
}

double State::getMouseScroll() const {
    return mouseScroll;
}

void State::setKey(int key, bool value) {
    keys[key] = value;
}

void State::setMouseX(double mouseX) {
    this->mouseX = mouseX;
}

void State::setMouseY(double mouseY) {
    this->mouseY = mouseY;
}

void State::setMouseScroll(double mouseScroll) {
    this->mouseScroll = mouseScroll;
}

Camera::Ptr &State::getCamera() {
    return camera;
}

void State::setCamera(const Camera::Ptr &camera) {
    State::camera = camera;
}

const Map::Ptr &State::getMap() const {
    return map;
}

void State::setMap(const Map::Ptr &map) {
    State::map = map;
}

bool State::isPaused() const {
    return paused;
}

bool State::shouldStop() const {
    return stopped;
}

void State::pause() {
    paused = true;
}

void State::unpause() {
    paused = false;
}

void State::start() {
    paused = false;
    stopped = false;
}

void State::stop() {
    stopped = true;
    lastFrameStart = std::chrono::system_clock::now();
}

void State::enterFrame() {
    auto currentFrame = std::chrono::system_clock::now();
    fps = 1.0 / std::chrono::duration<double>(currentFrame - lastFrameStart).count();
    lastFrameStart = currentFrame;
}

double State::getFPS() const {
    return fps;
}

