//
// Created by Philip on 2/25/2020.
//

#include "Interface.h"


Interface::Interface() {}

void Interface::update(const State::Ptr &state) {
    if (state->get_mouse_scroll() > 0)
        state->getScene().getCamera().zoomIn();
    else if (state->get_mouse_scroll() < 0)
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
    auto mx = state->get_mouse_x();
    auto my = state->get_mouse_y();
    float dx = 3.0*(mx - state->get_last_mouse_x())/cameraRect.get_width();
    float dy = 0.0*(my - state->get_last_mouse_y())/cameraRect.get_height();
    state->getScene().getCamera().panHorizontal(dx);
    state->getScene().getCamera().panVertical(dy);

    // set mouse pos to itself so the last mouse position is also set to the current mouse position
    state->set_mouse_x(mx);
    state->set_mouse_x(my);
}
