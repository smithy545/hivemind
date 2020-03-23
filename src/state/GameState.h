//
// Created by smith on 3/23/2020.
//

#ifndef SOCIETY_GAMESTATE_H
#define SOCIETY_GAMESTATE_H

#include <common/Entity.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>


class GameState {
public:
    typedef std::shared_ptr<GameState> Ptr;

    GameState();

    std::vector<Entity::Ptr> getEntities();

    bool getKey(int key) const;

    double getMouseX() const;

    double getMouseY() const;

    double getMouseScroll() const;

    void setKey(int key, bool value);

    void setMouseX(double mouseX);

    void setMouseY(double mouseY);

    void setMouseScroll(double mouseScroll);

private:
    // io state
    bool keys[GLFW_KEY_LAST];
    double mouseX{};
    double mouseY{};
    double mouseScroll{};

    std::vector<Entity::Ptr> loadedEntities;
};


#endif //SOCIETY_GAMESTATE_H
