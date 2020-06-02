//
// Created by Philip on 2/25/2020.
//

#include "Interface.h"


Interface::Interface() {}

void Interface::update(const State::Ptr &state) {
    auto camera = state->getScene().getCamera();
    if (state->getMouseScroll() > 0) {
        camera->zoomIn();
    } else if (state->getMouseScroll() < 0) {
        camera->zoomOut();
    }
    if (state->getKey(GLFW_KEY_LEFT)) {
        camera->panLeft();
    }
    if (state->getKey(GLFW_KEY_RIGHT)) {
        camera->panRight();
    }
    if (state->getKey(GLFW_KEY_UP)) {
        camera->panUp();
    }
    if (state->getKey(GLFW_KEY_DOWN)) {
        camera->panDown();
    }

    double mx = state->getMouseX();
    double my = state->getMouseY();
}
