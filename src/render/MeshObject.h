//
// Created by Philip on 3/1/2020.
//

#ifndef HIVEMIND_MESHOBJECT_H
#define HIVEMIND_MESHOBJECT_H

#include <glm/glm.hpp>
#include <utility>
#include <vector>

#include "Mesh.h"


class MeshObject {
public:
    typedef std::shared_ptr<MeshObject> Ptr;

    Mesh::Ptr mesh;
    std::vector<glm::mat4> models;

    explicit MeshObject(Mesh::Ptr mesh) : MeshObject(std::move(mesh), glm::mat4(1)) {}

    MeshObject(Mesh::Ptr mesh, glm::mat4 model) : mesh(std::move(mesh)), models({model}) {}

    MeshObject(Mesh::Ptr mesh, std::vector<glm::mat4> models) : mesh(std::move(mesh)), models(std::move(models)) {}
};


#endif //HIVEMIND_MESHOBJECT_H
