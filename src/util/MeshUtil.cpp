//
// Created by Philip on 3/1/2020.
//

#include "MeshUtil.h"

#include "RenderUtil.h"

#include "CImg.h"

using namespace cimg_library;


Mesh::Ptr MeshUtil::generateTileMesh(const std::string &texturePath, float tileSize) {
    Mesh::Ptr mesh = std::make_shared<Mesh>();

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

    mesh->textureId = RenderUtil::loadTexture(texturePath);

    mesh->reload();

    return mesh;
}

Mesh::Ptr MeshUtil::generateImageMesh(const std::string &imagePath) {
    // double load image for now but who cares
    CImg<unsigned char> img(("../res/img/" + imagePath).c_str());

    Mesh::Ptr mesh = std::make_shared<Mesh>();

    // bottom left
    mesh->vertices.push_back(0);
    mesh->vertices.push_back(0);

    mesh->uvs.push_back(0);
    mesh->uvs.push_back(0);

    // bottom right
    mesh->vertices.push_back(img.width());
    mesh->vertices.push_back(0);

    mesh->uvs.push_back(1);
    mesh->uvs.push_back(0);

    // top right
    mesh->vertices.push_back(img.width());
    mesh->vertices.push_back(img.height());

    mesh->uvs.push_back(1);
    mesh->uvs.push_back(1);

    // top left
    mesh->vertices.push_back(0);
    mesh->vertices.push_back(img.height());

    mesh->uvs.push_back(0);
    mesh->uvs.push_back(1);

    // indices
    mesh->indices.push_back(0);
    mesh->indices.push_back(2);
    mesh->indices.push_back(3);

    mesh->indices.push_back(1);
    mesh->indices.push_back(2);
    mesh->indices.push_back(0);

    mesh->textureId = RenderUtil::loadTexture(imagePath);

    mesh->reload();

    return mesh;
}
