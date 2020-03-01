//
// Created by Philip on 2/25/2020.
//

#ifndef HIVEMIND_RENDERABLE_H
#define HIVEMIND_RENDERABLE_H

#include "Mesh.h"


class Renderable {
public:
    virtual Mesh::Ptr generateMesh(float screenWidth, float screenHeight, float tileSize) = 0;
};

#endif //HIVEMIND_RENDERABLE_H
