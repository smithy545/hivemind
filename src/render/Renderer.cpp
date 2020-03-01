//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <fstream>
#include <iostream>


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
    glfwSetFramebufferSizeCallback(window, Renderer::resize);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    return window;
}

GLuint Renderer::loadShaderProgram(const std::string &name, const std::string &vertexShaderPath,
                                   const std::string &fragmentShaderPath) {
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    const char *vertexShaderSource = readShader(vertexShaderPath);
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
    const char *fragmentShaderSource = readShader(fragmentShaderPath);
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

void Renderer::renderMesh(const std::weak_ptr<Mesh> &meshPtr) {
    Mesh::Ptr mesh = meshPtr.lock();

    glBindVertexArray(mesh->getVertexArrayId());
    glDrawElements(GL_TRIANGLES, mesh->getNumIndices(), GL_UNSIGNED_INT, nullptr);
}

char *Renderer::readShader(const std::string &path) {
    std::ifstream shaderStream("../res/shaders/" + path, std::ifstream::ate);
    if (shaderStream) {
        // get file length (ifstream::ate flag puts cursor at end of file)
        int shaderLength = shaderStream.tellg();
        shaderStream.seekg(0, std::ios_base::beg);

        // store in buffer
        char *shaderBuffer = new char[shaderLength];
        int count = 0;
        while (shaderStream.read(shaderBuffer + count, shaderLength - count) || shaderStream.gcount() != 0) {
            count += shaderStream.gcount();
        }
        shaderStream.close();

        // null terminate because C++ fucking sucks
        shaderBuffer[count] = '\0';

        return shaderBuffer;
    }

    // open failed for some reason
    std::cout << "Error opening shader at res/shaders/" << path << std::endl;
    return nullptr;
}

void Renderer::resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow *Renderer::getWindow() const {
    return window;
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

const std::unordered_map<std::string, GLuint> &Renderer::getShaderPrograms() const {
    return shaderPrograms;
}
