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

    Sprite::Ptr mesh;
    std::vector<glm::mat4> models;

    explicit SpriteCollection(Sprite::Ptr mesh) : SpriteCollection(std::move(mesh), glm::mat4(1)) {}

    SpriteCollection(Sprite::Ptr mesh, glm::mat4 model) : mesh(std::move(mesh)), models({model}) {}

    SpriteCollection(Sprite::Ptr mesh, std::vector<glm::mat4> models) : mesh(std::move(mesh)),
                                                                        models(std::move(models)) {}
};


#endif //SOCIETY_SPRITECOLLECTION_H
