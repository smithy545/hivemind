//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_RENDERUTIL_H
#define SOCIETY_RENDERUTIL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <render/Sprite.h>
#include <string>


class RenderUtil {
public:
    static GLuint loadShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    static GLuint loadTexture(const std::string &texturePath, int &width, int &height);
};


#endif //SOCIETY_RENDERUTIL_H
