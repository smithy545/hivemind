//
// Created by Philip on 3/1/2020.
//

#ifndef WORKER_MESHUTIL_H
#define WORKER_MESHUTIL_H

#include "render/Sprite.h"


class SpriteUtil {
public:
    static Sprite::Ptr generateTileMesh(const std::string &texturePath, float tileSize);

    static Sprite::Ptr generateImageMesh(const std::string &imagePath);

    static Sprite::Ptr generateRectMesh(const std::string &imagePath, int width, int height);

    static Sprite::Ptr generateSpriteMesh(const std::string &jsonPath);
};


#endif //WORKER_MESHUTIL_H
