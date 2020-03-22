//
// Created by Philip on 2/25/2020.
//

#ifndef SOCIETY_USERINTERFACE_H
#define SOCIETY_USERINTERFACE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "render/Camera.h"
#include "render/Sprite.h"
#include "world/GridMap.h"

#include "UIEntity.h"


class UserInterface {
public:
    typedef std::shared_ptr<UserInterface> Ptr;

    explicit UserInterface(const std::string &configPath);

    void update(const bool keys[256],
                float mouseX,
                float mouseY,
                float mouseScroll,
                const GridMap::Ptr &map,
                const Camera::Ptr &camera,
                int tileSize);

    void add(int x, int y, std::string component);

    const std::vector<UIEntity::Ptr> &getEntities() const;

private:
    std::unordered_map<std::string, UIEntity::Ptr> availableComponents;
    std::vector<UIEntity::Ptr> loadedEntities;
};


#endif //SOCIETY_USERINTERFACE_H
