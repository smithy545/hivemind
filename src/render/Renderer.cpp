//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <iostream>

#include <glm/ext.hpp>

#include "RenderUtil.h"

Renderer::Renderer(int width, int height, int tileSize) : camera(
        std::make_shared<Camera>(0, 0, width, height, tileSize)),
                                                          width(width), height(height), tileSize(tileSize),
                                                          window(nullptr),
                                                          projectionMatrix(glm::ortho(
                                                                  .0f, 1.f * width,
                                                                  .0f, 1.f * height,
                                                                  -1.f, 1.f)) {}

void Renderer::cleanup() {
    for (auto &shaderProgram : shaderPrograms) {
        glDeleteProgram(shaderProgram.second);
    }
    // glfw: terminate, clearing all previously allocated GLFW resources
    // ------------------------------------------------------------------
    glfwTerminate();
}

std::shared_ptr<GLFWwindow> Renderer::init() {
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
    window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, "Hoovemind", nullptr, nullptr));
    if (window == nullptr) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window.get());

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    return window;
}

void Renderer::render(const std::vector<MeshObject::Ptr> &meshObjects, GLint mvpUniform) {
    //GLuint program = shaderPrograms["default"];
    //glUseProgram(program);
    glm::mat4 viewProj = projectionMatrix * camera->getViewMatrix();

    for (const MeshObject::Ptr &obj: meshObjects) {
        for (auto model: obj->models) {
            glm::mat4 mvpMatrix = viewProj * model;
            glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvpMatrix[0][0]);

            RenderUtil::renderMesh(obj->mesh);
        }
    }
}

GLuint Renderer::loadShaderProgram(const std::string &name, const std::string &vertexShaderPath,
                                   const std::string &fragmentShaderPath) {
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    const char *vertexShaderSource = RenderUtil::readShader(vertexShaderPath);
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
    const char *fragmentShaderSource = RenderUtil::readShader(fragmentShaderPath);
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

    // store shader locally
    shaderPrograms[name] = shaderProgram;

    return shaderProgram;
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
