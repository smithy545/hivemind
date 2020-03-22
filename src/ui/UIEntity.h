//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_UIENTITY_H
#define SOCIETY_UIENTITY_H

#include <memory>
#include <glm/glm.hpp>

#include "common/Entity.h"


class UIEntity : public Entity {
public:
    typedef std::shared_ptr<UIEntity> Ptr;

    UIEntity(const json &schema);

    json pack() override;

    bool unpack(json data) override;

    glm::mat4 getModel();

    int getX();

    int getY();

    int getWidth();

    int getHeight();

    bool resize(int width, int height);

    [[nodiscard]] const std::string &getSpriteName() const;
private:
    int x{};
    int y{};
    int width{};
    int height{};
    std::string spriteName{"ui_tile_0"};
};


#endif //SOCIETY_UIENTITY_H
