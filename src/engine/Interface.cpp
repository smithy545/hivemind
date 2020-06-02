//
// Created by Philip on 2/25/2020.
//

#include "Interface.h"


Interface::Interface() {}

void Interface::update(const State::Ptr &state) {
    auto camera = state->getScene().getCamera();
    if (state->getMouseScroll() > 0)
        camera->zoomIn();
    else if (state->getMouseScroll() < 0)
        camera->zoomOut();

    if (state->getKey(GLFW_KEY_W))
        camera->moveForward();
    if (state->getKey(GLFW_KEY_S))
        camera->moveBackword();
    if (state->getKey(GLFW_KEY_SPACE))
        camera->moveUp();
    if (state->getKey(GLFW_KEY_LEFT_CONTROL))
        camera->moveDown();
    if (state->getKey(GLFW_KEY_A))
        camera->strafeLeft();
    if (state->getKey(GLFW_KEY_D))
        camera->strafeRight();

    float dx = 3.0*(state->getMouseX() - state->getLastMouseX())/camera->getBoundingRect().getWidth();
    float dy = 0.0*(state->getMouseY() - state->getLastMouseY())/camera->getBoundingRect().getHeight();
    camera->panHorizontal(dx);
    camera->panVertical(dy);

    // set mouse pos to itself so the last mouse position is also set to the current mouse position
    state->setMouseX(state->getMouseX());
    state->setMouseY(state->getMouseY());
}
