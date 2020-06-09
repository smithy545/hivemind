//
// Created by Philip on 2/25/2020.
//

#include "Interface.h"


Interface::Interface() {}

void Interface::update(const State::Ptr &state) {
    if (state->getMouseScroll() > 0)
        state->getScene().getCamera().zoomIn();
    else if (state->getMouseScroll() < 0)
        state->getScene().getCamera().zoomOut();

    if (state->getKey(GLFW_KEY_W))
        state->getScene().getCamera().moveForward();
    if (state->getKey(GLFW_KEY_S))
        state->getScene().getCamera().moveBackword();
    if (state->getKey(GLFW_KEY_SPACE))
        state->getScene().getCamera().moveUp();
    if (state->getKey(GLFW_KEY_LEFT_CONTROL))
        state->getScene().getCamera().moveDown();
    if (state->getKey(GLFW_KEY_A))
        state->getScene().getCamera().strafeLeft();
    if (state->getKey(GLFW_KEY_D))
        state->getScene().getCamera().strafeRight();

    auto cameraRect = state->getScene().getCamera().getBoundingRect();
    auto mx = state->getMouseX();
    auto my = state->getMouseY();
    float dx = 3.0*(mx - state->getLastMouseX())/cameraRect.getWidth();
    float dy = 0.0*(my - state->getLastMouseY())/cameraRect.getHeight();
    state->getScene().getCamera().panHorizontal(dx);
    state->getScene().getCamera().panVertical(dy);

    // set mouse pos to itself so the last mouse position is also set to the current mouse position
    state->setMouseX(mx);
    state->setMouseY(my);
}
