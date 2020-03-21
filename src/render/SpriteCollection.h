//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_SPRITECOLLECTION_H
#define SOCIETY_SPRITECOLLECTION_H

#include <utility>
#include <vector>

#include <glm/glm.hpp>

#include "Sprite.h"


// TODO: Encapsulate models/mesh members and provide interface to interact with individual models
class SpriteCollection {
public:
    typedef std::shared_ptr<SpriteCollection> Ptr;

    explicit SpriteCollection(Sprite::Ptr sprite);

    SpriteCollection(Sprite::Ptr sprite, glm::mat4 model);

    SpriteCollection(Sprite::Ptr sprite, std::vector<glm::mat4> models);

    void addModel(glm::mat4 model);

    const Sprite::Ptr &getSprite() const;

    const std::vector<glm::mat4> &getModels() const;

    void clearModels();

private:
    Sprite::Ptr sprite;
    std::vector<glm::mat4> models;
};


#endif //SOCIETY_SPRITECOLLECTION_H
