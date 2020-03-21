//
// Created by Philip on 3/1/2020.
//

#ifndef WORKER_MESHUTIL_H
#define WORKER_MESHUTIL_H

#include <string>

#include <render/Sprite.h>


class SpriteUtil {
public:
    static Sprite::Ptr generateSpriteFromJson(const std::string &jsonPath, std::string &spriteName);
};


#endif //WORKER_MESHUTIL_H
