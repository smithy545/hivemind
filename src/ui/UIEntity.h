//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_UIENTITY_H
#define SOCIETY_UIENTITY_H

#include <memory>
#include <glm/glm.hpp>

#include "common/SchemaEntity.h"


class UIEntity : public SchemaEntity {
public:
    typedef std::shared_ptr<UIEntity> Ptr;

    explicit UIEntity(const json &schema);

    glm::mat4 getModel();

    [[nodiscard]] const std::string &getSpriteName() const;

private:
    std::string spriteName{"ui_tile_0"};
};


#endif //SOCIETY_UIENTITY_H
