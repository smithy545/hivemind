//
// Created by philip on 1/24/20.
//

#include <iostream>
#include <fstream>

#include "GameRunner.h"
#include "MapActor.h"


// settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

// static members
bool GameRunner::keys[];
double GameRunner::mouseX = 0.0f;
double GameRunner::mouseY = 0.0f;
GLFWwindow *GameRunner::window = nullptr;
Camera::Ptr GameRunner::camera = nullptr;

void GameRunner::loop() {
    // Initialise GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hoovemind", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, GameRunner::resize);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Setup keyboard inputs
    glfwSetKeyCallback(window, keyCallback);
    // Setup mouse inputs
    glfwSetCursorPosCallback(window, cursorPosCallback);
    // Setup text input
    glfwSetCharCallback(window, characterCallback);

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    const char *vertexShaderSource = readShader("vertex.shader");
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Error on vertex compilation: " << infoLog << std::endl;
    }
    delete[] vertexShaderSource;

    // fragment shader
    const char *fragmentShaderSource = readShader("fragment.shader");
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Error on fragment compilation: " << infoLog << std::endl;
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
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // activate shader program and setup uniforms
    glUseProgram(shaderProgram);
    GLdouble mouseXUniform = glGetUniformLocation(shaderProgram, "mouseX");
    GLdouble mouseYUniform = glGetUniformLocation(shaderProgram, "mouseY");
    GLint widthUniform = glGetUniformLocation(shaderProgram, "width");
    GLint heightUniform = glGetUniformLocation(shaderProgram, "height");

    // set constant uniforms
    glUniform1f(widthUniform, 32.0f/SCR_WIDTH);
    glUniform1f(heightUniform, 32.0f/SCR_HEIGHT);

    // set background to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // setup non opengl entites

    // map setup
    std::vector<GridMap::Ptr> loadedMaps;
    loadedMaps.push_back(std::make_shared<GridMap>(10, 10));

    // camera setup (camera not currently used)
    camera = std::make_shared<Camera>(0, 0, SCR_WIDTH, SCR_HEIGHT);

    do {
        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT);

        // update dynamic uniforms
        glUniform1d(mouseXUniform, mouseX);
        glUniform1d(mouseYUniform, mouseY);

        // update and render all maps
        for (const GridMap::Ptr &map: loadedMaps) {
            update(map);
            renderMesh(map->generateMesh(SCR_WIDTH, SCR_HEIGHT, 32));
        }

        // glfw: swap buffers and poll IO events
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    // clear maps to ensure explicit destruction of map meshes
    loadedMaps.clear();

    // glfw: terminate, clearing all previously allocated GLFW resources
    // ------------------------------------------------------------------
    glfwTerminate();
}

void GameRunner::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (action) {
        case GLFW_PRESS:
            keys[key] = true;
            break;
        case GLFW_RELEASE:
            keys[key] = false;
            break;
        case GLFW_REPEAT:
            break;
        default:
            std::cerr << "Key action \"" << action << "\" not handled" << std::endl;
    }
}

void GameRunner::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}

void GameRunner::characterCallback(GLFWwindow* window, unsigned int codepoint) { }

void GameRunner::renderMesh(const Mesh::Ptr& mesh) {
    glBindVertexArray(mesh->vertexArrayId);
    glDrawElements(GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT, nullptr);
}

void GameRunner::update(const GridMap::Ptr &map) {
    for (const MapActor::Ptr &actor: map->getActors()) {
        actor->update();
    }
}

void GameRunner::resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

char* GameRunner::readShader(const std::string& path) {
    std::ifstream shaderStream("../res/" + path, std::ifstream::ate);
    if(shaderStream) {
        // get file length (ifstream::ate flag puts cursor at end of file)
        int shaderLength = shaderStream.tellg();
        shaderStream.seekg(0, std::ios_base::beg);

        // store in buffer
        char* shaderBuffer = new char[shaderLength];
        int count = 0;
        while(shaderStream.read(shaderBuffer + count, shaderLength - count) || shaderStream.gcount() != 0) {
            count += shaderStream.gcount();
        }
        shaderStream.close();

        // null terminate because C++ fucking sucks
        shaderBuffer[count] = '\0';

        return shaderBuffer;
    }

    // open failed for some reason
    std::cout << "Error opening shader at res/" << path << std::endl;
    return nullptr;
}