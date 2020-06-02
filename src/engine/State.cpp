//
// Created by smith on 3/23/2020.
//

#include "State.h"


State::State(int width, int height) :   map(nullptr),
                                        scene(width, height),
                                        mouseX(width*0.5),
                                        mouseY(height*0.5),
                                        lastMouseX(width*0.5),
                                        lastMouseY(height*0.5) {
    for (bool &key : keys)
        key = false;
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

void State::setMouseX(double x) {
    lastMouseX = mouseX;
    mouseX = x;
}

void State::setMouseY(double y) {
    lastMouseY = mouseY;
    mouseY = y;
}

void State::setMouseScroll(double delta) {
    mouseScroll = delta;
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

Scene &State::getScene() {
    return scene;
}

double State::getLastMouseX() const {
    return lastMouseX;
}

double State::getLastMouseY() const {
    return lastMouseY;
}

