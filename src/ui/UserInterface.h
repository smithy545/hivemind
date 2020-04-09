//
// Created by Philip on 2/25/2020.
//

#ifndef SOCIETY_USERINTERFACE_H
#define SOCIETY_USERINTERFACE_H

#include <common/SchemaPrototype.h>
#include <memory>
#include <render/Camera.h>
#include <render/Renderer.h>
#include <render/Sprite.h>
#include <state/GameState.h>
#include <string>
#include <unordered_map>
#include <vector>


class UserInterface {
public:
    typedef std::shared_ptr<UserInterface> Ptr;

    explicit UserInterface(const std::string &configPath, const Renderer::Ptr &renderer);

    void addComponentAt(int x, int y, const std::string &componentType);

    void update(const GameState::Ptr &state, const Renderer::Ptr &renderer);

    const std::unordered_map<std::string, SchemaPrototype::Ptr> &getComponents() const;

    std::vector<SchemaPrototype::Ptr> getEntities();

private:
    std::unordered_map<std::string, SchemaPrototype::Ptr> components;
    unsigned int selectorId;
    int tileId{0};

    std::string getSelectedSprite();
};


#endif //SOCIETY_USERINTERFACE_H
