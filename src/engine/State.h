//
// Created by smith on 3/23/2020.
//

#ifndef SOCIETY_STATE_H
#define SOCIETY_STATE_H

#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "macros.h"
#include "pathing/Map.h"
#include "Scene.h"


class State {
public:
    POINTERIZE(State);

    typedef std::chrono::time_point<std::chrono::system_clock> timestamp;

    State(int width, int height);

    bool get_key(int key) const;

    void set_key(int key, bool value);

    void set_mouse_x(double x);

    void set_mouse_y(double y);

    void pause();

    void unpause();

    void start();

    void stop();

    double enter_frame();

    // game state
    _BVAR_GETSET(paused, public, private){true};
    _BVAR_GETSET(stopped, public, private){true};
    _VAR_GETSET(double, fps, public, private){0};
    _VAR_GETSET(timestamp, last_frame_start, public, private);

    // io state
    _VAR_GET(double, mouse_x, public){0};
    _VAR_GET(double, mouse_y, public){0};
    _VAR_GET(double, last_mouse_x, public){0};
    _VAR_GET(double, last_mouse_y, public){0};
    _VAR_GETSET(double, mouse_scroll, public, public){0};
private:
    bool keys[GLFW_KEY_LAST]{};
};


#endif //SOCIETY_STATE_H

