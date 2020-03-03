//
// Created by Philip on 3/1/2020.
//

#include "MeshUtil.h"

#include "RenderUtil.h"


Mesh::Ptr MeshUtil::generateTileMesh(float tileSize) {
    Mesh::Ptr tileMesh = std::make_shared<Mesh>();

    // top left
    tileMesh->vertices.push_back(0.f);
    tileMesh->vertices.push_back(0.f);

    // top right
    tileMesh->vertices.push_back(tileSize);
    tileMesh->vertices.push_back(0.f);

    // bottom left
    tileMesh->vertices.push_back(0.f);
    tileMesh->vertices.push_back(tileSize);

    // bottom right
    tileMesh->vertices.push_back(tileSize);
    tileMesh->vertices.push_back(tileSize);

    // texture coords
    tileMesh->uvs.push_back(0.0f);
    tileMesh->uvs.push_back(0.0f);

    tileMesh->uvs.push_back(1.0f);
    tileMesh->uvs.push_back(0.0f);

    tileMesh->uvs.push_back(0.0f);
    tileMesh->uvs.push_back(1.0f);

    tileMesh->uvs.push_back(1.0f);
    tileMesh->uvs.push_back(1.0f);

    // indices
    tileMesh->indices.push_back(0);
    tileMesh->indices.push_back(1);
    tileMesh->indices.push_back(2);

    tileMesh->indices.push_back(1);
    tileMesh->indices.push_back(2);
    tileMesh->indices.push_back(3);

    // load default texture
    tileMesh->textureId = RenderUtil::loadTexture("dailyshow.png");

    tileMesh->reload();

    return tileMesh;
}
