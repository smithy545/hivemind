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
    typedef std::shared_ptr<Renderer> Ptr;

    Renderer(int width, int height, int tileSize);

    GLFWwindow *init();

    void cleanup();

    void render(GLint mvpUniform);

    void resize(int width, int height);

    void storeMesh(const std::string &name, const Mesh::Ptr &mesh);

    const Camera::Ptr &getCamera() const;

    int getWidth() const;

    int getHeight() const;

    int getTileSize() const;

    GLuint getShader(const std::string &name);

    MeshObject::Ptr getMeshObject(const std::string &name);

private:
    int width;
    int height;
    int tileSize;

    Camera::Ptr camera;
    GLFWwindow *window;
    std::unordered_map<std::string, MeshObject::Ptr> loadedMeshes;
    std::unordered_map<std::string, GLuint> loadedShaders;
};


#endif //HIVEMIND_RENDERER_H
