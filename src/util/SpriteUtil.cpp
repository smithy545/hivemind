//
// Created by Philip on 3/1/2020.
//
#include "SpriteUtil.h"

#include <nlohmann/json.hpp>

#include "FileUtil.h"

using json = nlohmann::json;


Sprite::Ptr SpriteUtil::generateSpriteFromJson(const std::string &jsonPath, std::string &spriteName) {
    Sprite::Ptr sprite = std::make_shared<Sprite>();

    auto spriteData = FileUtil::readJsonFile(jsonPath);
    int width = spriteData["width"];
    int height = spriteData["height"];
    std::string name = spriteData["name"];
    std::string tex = spriteData["textureName"];
    sprite->texture = tex;

    // set output variable
    spriteName = name;

    // bottom left
    sprite->vertices.push_back(0);
    sprite->vertices.push_back(0);

    sprite->uvs.push_back(0);
    sprite->uvs.push_back(0);

    // bottom right
    sprite->vertices.push_back(width);
    sprite->vertices.push_back(0);

    sprite->uvs.push_back(1);
    sprite->uvs.push_back(0);

    // top right
    sprite->vertices.push_back(width);
    sprite->vertices.push_back(height);

    sprite->uvs.push_back(1);
    sprite->uvs.push_back(1);

    // top left
    sprite->vertices.push_back(0);
    sprite->vertices.push_back(height);

    sprite->uvs.push_back(0);
    sprite->uvs.push_back(1);

    // indices
    sprite->indices.push_back(0);
    sprite->indices.push_back(2);
    sprite->indices.push_back(3);

    sprite->indices.push_back(1);
    sprite->indices.push_back(2);
    sprite->indices.push_back(0);

    sprite->reload();

    return sprite;
}
