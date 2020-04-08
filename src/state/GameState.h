//
// Created by smith on 3/23/2020.
//

#ifndef SOCIETY_GAMESTATE_H
#define SOCIETY_GAMESTATE_H

#include <common/SchemaEntity.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <render/Camera.h>
#include <render/Scene.h>


class GameState : public Scene {
public:
    typedef std::shared_ptr<GameState> Ptr;

    GameState();

    std::vector<SchemaEntity::Ptr> getEntities() override;

    bool getKey(int key) const;

    double getMouseX() const;

    double getMouseY() const;

    double getMouseScroll() const;

    Camera::Ptr &getCamera() override;

    void addSchemaEntity(const SchemaEntity::Ptr &entity);

    void setKey(int key, bool value);

    void setMouseX(double mouseX);

    void setMouseY(double mouseY);

    void setMouseScroll(double mouseScroll);

    void setCamera(const Camera::Ptr &camera);

private:
    // io state
    bool keys[GLFW_KEY_LAST]{};
    double mouseX{};
    double mouseY{};
    double mouseScroll{};

    // scene state
    Camera::Ptr camera;
    std::vector<SchemaEntity::Ptr> entities;
};


#endif //SOCIETY_GAMESTATE_H
