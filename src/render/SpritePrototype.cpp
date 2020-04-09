//
// Created by smith on 4/9/2020.
//

#include "SpritePrototype.h"

SpritePrototype::SpritePrototype(Sprite::Ptr sprite) : SchemaPrototype(std::string("{}")), sprite(sprite) {}

const Sprite::Ptr &SpritePrototype::getSprite() const {
    return sprite;
}

void SpritePrototype::setSprite(const Sprite::Ptr &sprite) {
    SpritePrototype::sprite = sprite;
}
