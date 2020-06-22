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

    State(int width, int height);

    Scene &getScene();

    bool getKey(int key) const;

    const Map::Ptr &getMap() const;

    void setKey(int key, bool value);

    void setMap(const Map::Ptr &map);

    bool isPaused() const;

    bool shouldStop() const;

    void pause();

    void unpause();

    void start();

    void stop();

    void enterFrame();

    double getFPS() const;

private:
    // game state
    bool paused{true};
    bool stopped{true};
    std::chrono::time_point<std::chrono::system_clock> lastFrameStart;
    double fps{};

    // io state
    bool keys[GLFW_KEY_LAST]{};
    _VAR(double,mouse_x,public,public,0)
    _VAR(double,mouse_y,public,public,0)
    _VAR(double,last_mouse_x,public,private,0)
    _VAR(double,last_mouse_y,public,private,0)
    _VAR(double,mouse_scroll,public,public,0);

    // scene state
    Scene scene;

    // world state
    Map::Ptr map;
};


#endif //SOCIETY_STATE_H

