//
// Created by Philip on 3/1/2020.
//

#include "RenderUtil.h"

#include <iostream>

#include "CImg.h"
#include "FileUtil.h"

using namespace cimg_library;


void RenderUtil::renderMesh(const std::weak_ptr<Mesh> &meshPtr) {
    Mesh::Ptr mesh = meshPtr.lock();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->textureId);

    glBindVertexArray(mesh->vertexArrayId);
    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, nullptr);
}


GLuint RenderUtil::loadShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    char *vertexShaderSource = FileUtil::readResourceFile("shaders/" + vertexShaderPath);
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Error on vertex compilation: " << infoLog << std::endl;
        return -1;
    }
    delete[] vertexShaderSource;

    // fragment shader
    char *fragmentShaderSource = FileUtil::readResourceFile("shaders/" + fragmentShaderPath);
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Error on fragment compilation: " << infoLog << std::endl;
        return -1;
    }
    delete[] fragmentShaderSource;

    // compile shader program
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Error linking program: " << infoLog << std::endl;
        return -1;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}


GLuint RenderUtil::loadTexture(const std::string &texturePath) {
    // Make sure imagemagick and graphicsmagick installed for img loading
    CImg<unsigned char> image(("../res/img/" + texturePath).c_str());

    // interleave color data
    auto *data = new unsigned char[image.size()];
    int N = image.width() * image.height();
    for (int i = 0; i < N; i++) {
        data[3 * i] = image.data()[i];
        data[3 * i + 1] = image.data()[i + N];
        data[3 * i + 2] = image.data()[i + 2 * N];
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    delete[] data;

    std::cout << "Texture " << texturePath << " loaded" << std::endl;

    return textureID;
}
