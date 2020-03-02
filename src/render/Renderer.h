//
// Created by Philip on 3/1/2020.
//

#ifndef HIVEMIND_RENDERER_H
#define HIVEMIND_RENDERER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "MeshObject.h"


class Renderer {
public:
    Renderer(int width, int height, int tileSize);


    GLFWwindow* init();

    void cleanup();

    void render(const std::vector<MeshObject::Ptr> &meshObjects, GLint mvpUniform);

    const Camera::Ptr &getCamera() const;

    int getWidth() const;

    int getHeight() const;

    int getTileSize() const;

    GLuint loadShaderProgram(const std::string &name, const std::string &vertexShaderPath,
                             const std::string &fragmentShaderPath);

private:
    GLFWwindow* window;
    Camera::Ptr camera;
    int width;
    int height;
    int tileSize;
    std::unordered_map<std::string, GLuint> shaderPrograms;
    glm::mat4 projectionMatrix;

};


#endif //HIVEMIND_RENDERER_H
