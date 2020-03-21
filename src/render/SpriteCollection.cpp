//
// Created by smith on 3/16/2020.
//

#include "SpriteCollection.h"

SpriteCollection::SpriteCollection(Sprite::Ptr sprite) : SpriteCollection(std::move(sprite), glm::mat4(1)) {}

SpriteCollection::SpriteCollection(Sprite::Ptr sprite, glm::mat4 model) : sprite(std::move(sprite)), models({model}) {}

SpriteCollection::SpriteCollection(Sprite::Ptr sprite, std::vector<glm::mat4> models) : sprite(std::move(sprite)),
                                                                                        models(std::move(models)) {}

void SpriteCollection::addModel(glm::mat4 model) {
    models.push_back(model);
}

const Sprite::Ptr &SpriteCollection::getSprite() const {
    return sprite;
}

const std::vector<glm::mat4> &SpriteCollection::getModels() const {
    return models;
}

void SpriteCollection::clearModels() {
    models.clear();
}