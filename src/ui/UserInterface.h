//
// Created by Philip on 2/25/2020.
//

#ifndef SOCIETY_USERINTERFACE_H
#define SOCIETY_USERINTERFACE_H

#include <memory>
#include <render/Camera.h>
#include <render/Sprite.h>
#include <state/GameState.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <world/GridMap.h>

#include "UIEntity.h"


class UserInterface {
public:
    typedef std::shared_ptr<UserInterface> Ptr;

    explicit UserInterface(const std::string &configPath);

    void update(GameState::Ptr state);

    void add(int x, int y, const std::string &component);

    [[nodiscard]] const std::vector<UIEntity::Ptr> &getEntities() const;

private:

    std::unordered_map<std::string, UIEntity::Ptr> availableComponents;
    std::vector<UIEntity::Ptr> loadedEntities;
};


#endif //SOCIETY_USERINTERFACE_H
