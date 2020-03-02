//
// Created by Philip on 3/1/2020.
//

#include "MeshUtil.h"


Mesh::Ptr MeshUtil::generateTileMesh(float tileSize) {
    Mesh::Ptr tileMesh = std::make_shared<Mesh>();
    tileMesh->vertices.push_back(0.f);
    tileMesh->vertices.push_back(0.f);

    tileMesh->vertices.push_back(tileSize);
    tileMesh->vertices.push_back(0.f);

    tileMesh->vertices.push_back(0.f);
    tileMesh->vertices.push_back(tileSize);

    tileMesh->vertices.push_back(tileSize);
    tileMesh->vertices.push_back(tileSize);

    tileMesh->indices.push_back(0);
    tileMesh->indices.push_back(1);
    tileMesh->indices.push_back(2);

    tileMesh->indices.push_back(1);
    tileMesh->indices.push_back(2);
    tileMesh->indices.push_back(3);

    tileMesh->reload();

    return tileMesh;
}
