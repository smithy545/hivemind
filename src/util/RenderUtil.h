//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_RENDERUTIL_H
#define SOCIETY_RENDERUTIL_H

#include <memory>

#include "render/Mesh.h"


class RenderUtil {
public:
    static void renderMesh(const std::weak_ptr<Mesh> &mesh);

    static GLuint loadShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    static GLuint loadTexture(const std::string &texturePath);
};


#endif //SOCIETY_RENDERUTIL_H
