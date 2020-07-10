//
// Created by smith on 3/23/2020.
//

#include "State.h"


State::State(int width, int height) :   _mouse_x(width*0.5),
                                        _mouse_y(height*0.5),
                                        _last_mouse_x(width*0.5),
                                        _last_mouse_y(height*0.5) {
    for (bool &key : keys)
        key = false;
}

void State::pause() {
    _paused = true;
}

void State::unpause() {
    _paused = false;
}

void State::start() {
    _paused = false;
    _stopped = false;
    _last_frame_start = std::chrono::system_clock::now();
}

void State::stop() {
    _stopped = true;
    _last_frame_start = std::chrono::system_clock::now();
}

double State::enter_frame() {
    auto frame_start = std::chrono::system_clock::now();
    auto diff = std::chrono::duration<double>(frame_start - _last_frame_start).count();
    _fps = 1.0 / diff;
    _last_frame_start = frame_start;
    return diff;
}

bool State::get_key(int key) const {
    return keys[key];
}

void State::set_key(int key, bool value) {
    keys[key] = value;
}

void State::set_mouse_x(double x) {
    _last_mouse_x = _mouse_x;
    _mouse_x = x;
}

void State::set_mouse_y(double y) {
    _last_mouse_y = _mouse_y;
    _mouse_y = y;
}
