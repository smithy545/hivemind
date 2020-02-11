//
// Created by philip on 1/24/20.
//

#include <iostream>

#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GameRunner.h"
#include "MapActor.h"


// settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec2 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                                 "}\n\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                                   "}\n\0";

bool GameRunner::keys[];
GLFWwindow *GameRunner::window = nullptr;
Camera::Ptr GameRunner::camera = nullptr;


void GameRunner::loop(const std::vector<GridMap::Ptr> &loadedMaps) {
    // Initialise GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
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
    });

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
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
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Error on fragment compilation: " << infoLog << std::endl;
    }
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

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    camera = std::make_shared<Camera>(0, 0, SCR_WIDTH, SCR_HEIGHT);

    do {
        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);

        for (const GridMap::Ptr &map: loadedMaps) {
            update(map);
            render(map, VAO, VBO, EBO);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);


    glBindVertexArray(0);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void GameRunner::render(const GridMap::Ptr &map, int VAO, int VBO, int EBO) {
    int N = map->getNodes().size();
    auto *vertices = new float[8 * N];
    auto *indices = new unsigned int[6 * N];
    int i = 0;
    int j = 0;
    for (auto node: map->getNodes()) {
        float th = 2;
        float tw = 2;
        float x = node->x * tw - camera->x - SCR_WIDTH;
        float y = node->y * th - camera->y - SCR_HEIGHT;

        // top right
        vertices[i] = (x + tw) / SCR_WIDTH;
        vertices[i + 1] = y / SCR_HEIGHT;
        // bottom right
        vertices[i + 2] = (x + tw) / SCR_WIDTH;
        vertices[i + 3] = (y + th) / SCR_HEIGHT;
        // bottom left
        vertices[i + 4] = x / SCR_WIDTH;
        vertices[i + 5] = (y + th) / SCR_HEIGHT;
        // top left
        vertices[i + 6] = x / SCR_WIDTH;
        vertices[i + 7] = y / SCR_HEIGHT;

        indices[j] = i / 2;
        indices[j + 1] = i / 2 + 1;
        indices[j + 2] = i / 2 + 3;
        indices[j + 3] = i / 2 + 1;
        indices[j + 4] = i / 2 + 2;
        indices[j + 5] = i / 2 + 3;

        i += 8;
        j += 6;
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 8 * N * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * N * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6 * N, GL_UNSIGNED_INT, nullptr);
}

void GameRunner::update(const GridMap::Ptr &map) {
    for (const MapActor::Ptr &actor: map->getActors()) {
        actor->update();
    }
}

void GameRunner::resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}