//
// Created by Philip on 3/1/2020.
//

#ifndef WORKER_MESHUTIL_H
#define WORKER_MESHUTIL_H

#include "render/Mesh.h"


class MeshUtil {
public:
    static Mesh::Ptr generateTileMesh(const std::string &texturePath, float tileSize);

    static Mesh::Ptr generateImageMesh(const std::string &imagePath);

    static Mesh::Ptr generateRectMesh(const std::string &imagePath, int width, int height);
};


#endif //WORKER_MESHUTIL_H
