//
// Created by Philip on 3/1/2020.
//

#include "MeshUtil.h"

#include "RenderUtil.h"


Mesh::Ptr MeshUtil::generateTileMesh(const std::string &texturePath, float tileSize) {
    Mesh::Ptr tileMesh = std::make_shared<Mesh>();

    // bottom left
    tileMesh->vertices.push_back(0);
    tileMesh->vertices.push_back(0);

    tileMesh->uvs.push_back(0);
    tileMesh->uvs.push_back(0);

    // bottom right
    tileMesh->vertices.push_back(tileSize);
    tileMesh->vertices.push_back(0);

    tileMesh->uvs.push_back(1);
    tileMesh->uvs.push_back(0);

    // top right
    tileMesh->vertices.push_back(tileSize);
    tileMesh->vertices.push_back(tileSize);

    tileMesh->uvs.push_back(1);
    tileMesh->uvs.push_back(1);

    // top left
    tileMesh->vertices.push_back(0);
    tileMesh->vertices.push_back(tileSize);

    tileMesh->uvs.push_back(0);
    tileMesh->uvs.push_back(1);

    // indices
    tileMesh->indices.push_back(0);
    tileMesh->indices.push_back(2);
    tileMesh->indices.push_back(3);

    tileMesh->indices.push_back(1);
    tileMesh->indices.push_back(2);
    tileMesh->indices.push_back(0);

    // load default texture
    tileMesh->textureId = RenderUtil::loadTexture(texturePath);

    tileMesh->reload();

    return tileMesh;
}
