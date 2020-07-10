//
// Created by Philip on 2/25/2020.
//

#include "Interface.h"


void Interface::update(const State::Ptr &state, Scene::Ptr &scene, God::Ptr &god) {
    auto camera = scene->get_camera();
    if (state->get_mouse_scroll() > 0)
        camera->zoom_in();
    else if (state->get_mouse_scroll() < 0)
        camera->zoom_out();

    if (state->get_key(GLFW_KEY_W))
        camera->move_forward();
    if (state->get_key(GLFW_KEY_S))
        camera->move_backword();
    if (state->get_key(GLFW_KEY_SPACE))
        camera->move_up();
    if (state->get_key(GLFW_KEY_LEFT_CONTROL))
        camera->move_down();
    if (state->get_key(GLFW_KEY_A))
        camera->strafe_left();
    if (state->get_key(GLFW_KEY_D))
        camera->strafe_right();

    auto camera_bound = camera->get_bounding_rect();
    auto mx = state->get_mouse_x();
    auto my = state->get_mouse_y();

    // pan horizontal if necessary
    float dx = 3.0 * (mx - state->get_last_mouse_x()) / camera_bound.get_width();
    camera->pan_horizontal(dx);

    // set mouse pos to itself so the last mouse position is also set to the current mouse position
    state->set_mouse_x(mx);
    state->set_mouse_y(my);
}
