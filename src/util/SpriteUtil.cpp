//
// Created by Philip on 3/1/2020.
//

#include "FileUtil.h"
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include "SpriteUtil.h"
#include "RenderUtil.h"


Sprite::Ptr SpriteUtil::generateTileMesh(const std::string &texturePath, float tileSize) {
    Sprite::Ptr mesh = std::make_shared<Sprite>();

    // bottom left
    mesh->vertices.push_back(0);
    mesh->vertices.push_back(0);

    mesh->uvs.push_back(0);
    mesh->uvs.push_back(0);

    // bottom right
    mesh->vertices.push_back(tileSize);
    mesh->vertices.push_back(0);

    mesh->uvs.push_back(1);
    mesh->uvs.push_back(0);

    // top right
    mesh->vertices.push_back(tileSize);
    mesh->vertices.push_back(tileSize);

    mesh->uvs.push_back(1);
    mesh->uvs.push_back(1);

    // top left
    mesh->vertices.push_back(0);
    mesh->vertices.push_back(tileSize);

    mesh->uvs.push_back(0);
    mesh->uvs.push_back(1);

    // indices
    mesh->indices.push_back(0);
    mesh->indices.push_back(2);
    mesh->indices.push_back(3);

    mesh->indices.push_back(1);
    mesh->indices.push_back(2);
    mesh->indices.push_back(0);

    int width, height;
    mesh->textureId = RenderUtil::loadTexture(texturePath, width, height);

    mesh->reload();

    return mesh;
}

Sprite::Ptr SpriteUtil::generateImageMesh(const std::string &imagePath) {
    Sprite::Ptr mesh = std::make_shared<Sprite>();

    int width, height;
    mesh->textureId = RenderUtil::loadTexture(imagePath, width, height);

    // bottom left
    mesh->vertices.push_back(0);
    mesh->vertices.push_back(0);

    mesh->uvs.push_back(0);
    mesh->uvs.push_back(0);

    // bottom right
    mesh->vertices.push_back(width);
    mesh->vertices.push_back(0);

    mesh->uvs.push_back(1);
    mesh->uvs.push_back(0);

    // top right
    mesh->vertices.push_back(width);
    mesh->vertices.push_back(height);

    mesh->uvs.push_back(1);
    mesh->uvs.push_back(1);

    // top left
    mesh->vertices.push_back(0);
    mesh->vertices.push_back(height);

    mesh->uvs.push_back(0);
    mesh->uvs.push_back(1);

    // indices
    mesh->indices.push_back(0);
    mesh->indices.push_back(2);
    mesh->indices.push_back(3);

    mesh->indices.push_back(1);
    mesh->indices.push_back(2);
    mesh->indices.push_back(0);

    mesh->reload();

    return mesh;
}

Sprite::Ptr SpriteUtil::generateRectMesh(const std::string &imagePath, int width, int height) {
    Sprite::Ptr mesh = std::make_shared<Sprite>();
    int imWidth, imHeight;
    mesh->textureId = RenderUtil::loadTexture(imagePath, imWidth, imHeight);

    // bottom left
    mesh->vertices.push_back(0);
    mesh->vertices.push_back(0);

    mesh->uvs.push_back(0);
    mesh->uvs.push_back(0);

    // bottom right
    mesh->vertices.push_back(width);
    mesh->vertices.push_back(0);

    mesh->uvs.push_back(1);
    mesh->uvs.push_back(0);

    // top right
    mesh->vertices.push_back(width);
    mesh->vertices.push_back(height);

    mesh->uvs.push_back(1);
    mesh->uvs.push_back(1);

    // top left
    mesh->vertices.push_back(0);
    mesh->vertices.push_back(height);

    mesh->uvs.push_back(0);
    mesh->uvs.push_back(1);

    // indices
    mesh->indices.push_back(0);
    mesh->indices.push_back(2);
    mesh->indices.push_back(3);

    mesh->indices.push_back(1);
    mesh->indices.push_back(2);
    mesh->indices.push_back(0);

    mesh->reload();

    return mesh;
}

Sprite::Ptr SpriteUtil::generateSpriteMesh(const std::string &jsonPath) {
    json spriteData = FileUtil::readJsonFile(jsonPath);

    Sprite::Ptr mesh = std::make_shared<Sprite>();

    for (std::string tex: spriteData["textures"]) {
        std::cout << tex << std::endl;
    }

    return mesh;
}
