//
// Created by Philip on 2/25/2020.
//

#ifndef SOCIETY_USERINTERFACE_H
#define SOCIETY_USERINTERFACE_H

#include <common/SchemaEntity.h>
#include <memory>
#include <render/Camera.h>
#include <render/Sprite.h>
#include <state/GameState.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <world/GridMap.h>


class UserInterface {
public:
    typedef std::shared_ptr<UserInterface> Ptr;

    explicit UserInterface(const std::string &configPath);

    void addComponentAt(int x, int y, const std::string &componentType);

    void update(const GameState::Ptr &state);

    const std::unordered_map<std::string, SchemaEntity::Ptr> &getComponents() const;

    std::vector<SchemaEntity::Ptr> getComponentEntities();

private:
    std::unordered_map<std::string, SchemaEntity::Ptr> components;
};


#endif //SOCIETY_USERINTERFACE_H
