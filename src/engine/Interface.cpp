//
// Created by Philip on 2/25/2020.
//

#include "Interface.h"


void Interface::update(const State::Ptr &state, Camera &camera) {
    if (state->get_mouse_scroll() > 0)
        camera.zoom_in();
    else if (state->get_mouse_scroll() < 0)
        camera.zoom_out();

    if (state->get_key(GLFW_KEY_W))
        camera.move_forward();
    if (state->get_key(GLFW_KEY_S))
        camera.move_backword();
    if (state->get_key(GLFW_KEY_SPACE))
        camera.move_up();
    if (state->get_key(GLFW_KEY_LEFT_CONTROL))
        camera.move_down();
    if (state->get_key(GLFW_KEY_A))
        camera.strafe_left();
    if (state->get_key(GLFW_KEY_D))
        camera.strafe_right();
    if (state->get_key(GLFW_KEY_Q))
        camera.pan_horizontal(-0.05);
    if(state->get_key(GLFW_KEY_E))
        camera.pan_horizontal(0.05);

    auto camera_bound = camera.get_bounding_rect();
    auto mx = state->get_mouse_x();
    auto my = state->get_mouse_y();

    // set mouse pos to itself so the last mouse position is also set to the current mouse position
    state->set_mouse_x(mx);
    state->set_mouse_y(my);
}
