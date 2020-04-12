//
// Created by smith on 3/23/2020.
//

#ifndef SOCIETY_GAMESTATE_H
#define SOCIETY_GAMESTATE_H

#include <common/SchemaObject.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <render/Camera.h>
#include <world/WorldMap.h>
#include <world/WorldEntity.h>
#include <ui/UIEntity.h>


class GameState {
public:
    typedef std::shared_ptr<GameState> Ptr;

    GameState();

    const std::vector<WorldEntity::Ptr> &getWorldEntities() const;

    const std::vector<UIEntity::Ptr> &getUiEntities() const;

    bool getKey(int key) const;

    double getMouseX() const;

    double getMouseY() const;

    double getMouseScroll() const;

    Camera::Ptr &getCamera();

    const WorldMap::Ptr &getMap() const;

    void setKey(int key, bool value);

    void setMouseX(double mouseX);

    void setMouseY(double mouseY);

    void setMouseScroll(double mouseScroll);

    void setCamera(const Camera::Ptr &camera);

    void setMap(const WorldMap::Ptr &map);

private:
    // io state
    bool keys[GLFW_KEY_LAST]{};
    double mouseX{};
    double mouseY{};
    double mouseScroll{};

    // scene state
    Camera::Ptr camera;
    std::vector<WorldEntity::Ptr> worldEntities;
    std::vector<UIEntity::Ptr> uiEntities;

    // world state
    WorldMap::Ptr map;
};


#endif //SOCIETY_GAMESTATE_H

