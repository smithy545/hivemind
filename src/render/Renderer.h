//
// Created by Philip on 3/1/2020.
//

#ifndef HIVEMIND_RENDERER_H
#define HIVEMIND_RENDERER_H

#include <memory>
#include <string>
#include <unordered_map>

#include "src/render/Camera.h"
#include "Mesh.h"


class Renderer {
public:
    Renderer(int width, int height, int tileSize);

    GLFWwindow *init();

    GLuint loadShaderProgram(const std::string &name, const std::string &vertexShaderPath,
                             const std::string &fragmentShaderPath);

    GLFWwindow *getWindow() const;

    const Camera::Ptr &getCamera() const;

    int getWidth() const;

    int getHeight() const;

    int getTileSize() const;

    const std::unordered_map<std::string, GLuint> &getShaderPrograms() const;

    // render functions
    static void renderMesh(const std::weak_ptr<Mesh> &mesh);

    static char *readShader(const std::string &path);

    static void resize(GLFWwindow *window, int width, int height);

private:
    GLFWwindow *window;
    Camera::Ptr camera;
    int width;
    int height;
    int tileSize;
    std::unordered_map<std::string, GLuint> shaderPrograms;
};


#endif //HIVEMIND_RENDERER_H
