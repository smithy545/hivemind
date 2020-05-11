//
// Created by smith on 3/23/2020.
//

#ifndef SOCIETY_GAMESTATE_H
#define SOCIETY_GAMESTATE_H

#include <common/SchemaObject.h>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <pathing/Map.h>
#include <render/Camera.h>
#include <render/RenderNode.h>

class GameState {
public:
    typedef std::shared_ptr<GameState> Ptr;

    GameState();

    RenderNode::Ptr getRenderTree();

    bool getKey(int key) const;

    double getMouseX() const;

    double getMouseY() const;

    double getMouseScroll() const;

    Camera::Ptr &getCamera();

    const Map::Ptr &getMap() const;

    void setKey(int key, bool value);

    void setMouseX(double mouseX);

    void setMouseY(double mouseY);

    void setMouseScroll(double mouseScroll);

    void setCamera(const Camera::Ptr &camera);

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
    double mouseX{};
    double mouseY{};
    double mouseScroll{};

    // scene state
    Camera::Ptr camera;

    // world state
    Map::Ptr map;
};


#endif //SOCIETY_GAMESTATE_H

