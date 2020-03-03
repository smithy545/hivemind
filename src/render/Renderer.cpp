//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <iostream>

#include "util/MeshUtil.h"
#include "util/RenderUtil.h"


Renderer::Renderer(int width, int height, int tileSize) : camera(
        std::make_shared<Camera>(0, 0, width, height, tileSize)),
                                                          width(width), height(height), tileSize(tileSize),
                                                          window(nullptr) {}


GLFWwindow *Renderer::init() {
    // Initialise GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "Hoovemind", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // setup default shader
    loadedShaders["default"] = RenderUtil::loadShaderProgram("vertex.shader", "fragment.shader");

    // setup default mesh
    Mesh::Ptr tileMesh = MeshUtil::generateTileMesh(tileSize);
    storeMesh("tile", tileMesh);

    return window;
}

void Renderer::cleanup() {
    // clear loaded meshes
    loadedMeshes.clear();

    // clear loaded shaders
    for (auto &shaderProgram : loadedShaders) {
        glDeleteProgram(shaderProgram.second);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources
    glfwTerminate();
}

void Renderer::render(GLint mvpUniform) {
    //GLuint program = loadedShaders["default"];
    //glUseProgram(program);

    glm::mat4 viewProj = camera->getViewProjectionMatrix();
    for (const auto &obj: loadedMeshes) {
        for (auto model: obj.second->models) {
            glm::mat4 mvpMatrix = viewProj * model;
            glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvpMatrix[0][0]);

            RenderUtil::renderMesh(obj.second->mesh);
        }
    }
}

void Renderer::resize(int width, int height) {
    this->width = width;
    this->height = height;
    camera->resize(width, height);
}

GLuint Renderer::getShader(const std::string &name) {
    return loadedShaders[name];
}

MeshObject::Ptr Renderer::getMeshObject(const std::string &name) {
    return loadedMeshes[name];
}

void Renderer::storeMesh(const std::string &name, const Mesh::Ptr &mesh) {
    loadedMeshes[name] = std::make_shared<MeshObject>(mesh);
}

const Camera::Ptr &Renderer::getCamera() const {
    return camera;
}

int Renderer::getWidth() const {
    return width;
}

int Renderer::getHeight() const {
    return height;
}

int Renderer::getTileSize() const {
    return tileSize;
}
