//
// Created by Philip on 3/1/2020.
//

#ifndef HIVEMIND_RENDERUTIL_H
#define HIVEMIND_RENDERUTIL_H

#include <memory>

#include "render/Mesh.h"


class RenderUtil {
public:
    static void renderMesh(const std::weak_ptr<Mesh> &mesh);

    static GLuint loadShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    static GLuint loadTexture(const std::string &texturePath);
};


#endif //HIVEMIND_RENDERUTIL_H
