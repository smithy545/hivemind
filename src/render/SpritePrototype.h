//
// Created by smith on 4/9/2020.
//

#ifndef SOCIETY_SPRITEPROTOTYPE_H
#define SOCIETY_SPRITEPROTOTYPE_H

#include <common/SchemaPrototype.h>
#include <memory>

#include "Sprite.h"

class SpritePrototype : public SchemaPrototype {
public:
    typedef std::shared_ptr<SpritePrototype> Ptr;

    SpritePrototype(Sprite::Ptr sprite);

    const Sprite::Ptr &getSprite() const;

    void setSprite(const Sprite::Ptr &sprite);

private:
    Sprite::Ptr sprite;
};


#endif //SOCIETY_SPRITEPROTOTYPE_H
