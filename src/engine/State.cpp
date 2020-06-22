//
// Created by smith on 3/23/2020.
//

#include "State.h"


State::State(int width, int height) :   map(nullptr),
                                        scene(width, height),
                                        _mouse_x(width*0.5),
                                        _mouse_y(height*0.5),
                                        _last_mouse_x(width*0.5),
                                        _last_mouse_y(height*0.5) {
    for (bool &key : keys)
        key = false;
}

bool State::getKey(int key) const {
    return keys[key];
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
    lastFrameStart = std::chrono::system_clock::now();
}

void State::stop() {
    stopped = true;
    lastFrameStart = std::chrono::system_clock::now();
}

void State::enterFrame() {
    auto currentFrameStart = std::chrono::system_clock::now();
    fps = 1.0 / std::chrono::duration<double>(currentFrameStart - lastFrameStart).count();
    lastFrameStart = currentFrameStart;
}

double State::getFPS() const {
    return fps;
}

Scene &State::getScene() {
    return scene;
}
