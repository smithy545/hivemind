//
// Created by Philip on 3/1/2020.
//

#ifndef WORKER_MESHUTIL_H
#define WORKER_MESHUTIL_H

#include "render/Mesh.h"


class MeshUtil {
public:
    static Mesh::Ptr generateTileMesh(float tileSize);
};


#endif //WORKER_MESHUTIL_H
