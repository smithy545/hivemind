//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_SPRITEUTIL_H
#define SOCIETY_SPRITEUTIL_H

#include <render/Sprite.h>
#include <string>


class SpriteUtil {
public:
    static Sprite::Ptr generateSpriteFromJson(const std::string &jsonPath, std::string &spriteName);
};


#endif //SOCIETY_SPRITEUTIL_H
