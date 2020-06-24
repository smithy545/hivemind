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
    _BVAR_GETSET_INIT(paused, public, private, true)
    _BVAR_GETSET_INIT(stopped, public, private, true)
    _VAR_GETSET_INIT(fps, double, public, private, 0)
    _VAR_GETSET(last_frame_start, timestamp, public, private)

    // world state
    _MVAR_GETSET_INIT(map, Map::Ptr, public, public, nullptr)
    _MVAR_GETSET(scene, Scene::Ptr, public, public)

    // io state
    _VAR_GET_INIT(mouse_x, double, public, 0)
    _VAR_GET_INIT(mouse_y, double, public, 0)
    _VAR_GET_INIT(last_mouse_x, double, public, 0)
    _VAR_GET_INIT(last_mouse_y, double, public, 0)
    _VAR_GETSET_INIT(mouse_scroll, double, public, public, 0)
private:
    bool keys[GLFW_KEY_LAST]{};
};


#endif //SOCIETY_STATE_H

