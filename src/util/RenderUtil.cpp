//
// Created by Philip on 3/1/2020.
//

#include "RenderUtil.h"

#include <fstream>
#include <iostream>


void RenderUtil::renderMesh(const std::weak_ptr<Mesh> &meshPtr) {
    Mesh::Ptr mesh = meshPtr.lock();

    glBindVertexArray(mesh->vertexArrayId);
    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, nullptr);
}
