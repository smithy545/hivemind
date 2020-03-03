//
// Created by philip on 1/24/20.
//

#include "GameRunner.h"

#include <iostream>
#include <memory>

#include "render/Renderer.h"
#include "world/Human.h"


// static members
bool GameRunner::keys[];
int GameRunner::screenWidth = 800;
int GameRunner::screenHeight = 600;
float GameRunner::mouseX = 0;
float GameRunner::mouseY = 0;
float GameRunner::mouseScroll = 0;
bool GameRunner::resized = false;
unsigned int WorldEntity::GLOBAL_ID = 0;

void GameRunner::loop() {
    std::cout << "Renderer init" << std::endl;

    // instantiate renderer and get created window
    Renderer::Ptr renderer = std::make_shared<Renderer>(screenWidth, screenHeight, 64);
    GLFWwindow *window = renderer->init();

    std::cout << "Window init" << std::endl;

    for (bool &key : keys)
        key = false;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Setup keyboard inputs
    glfwSetKeyCallback(window, keyCallback);
    // Setup mouse inputs
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
    // Setup text input
    glfwSetCharCallback(window, characterCallback);
    // Window resize
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    std::cout << "Shader init" << std::endl;

    // activate shader program and setup uniforms
    GLuint defaultShader = renderer->getShader("default");
    glUseProgram(defaultShader);
    GLint mvpUniform = glGetUniformLocation(defaultShader, "MVP");
    GLint mouseXUniform = glGetUniformLocation(defaultShader, "mouseX");
    GLint mouseYUniform = glGetUniformLocation(defaultShader, "mouseY");

    // setup texture space in shader program to use active texture unit 0
    GLint texUniform = glGetUniformLocation(defaultShader, "tex");
    glUniform1i(texUniform, 0);

    std::cout << "Map init" << std::endl;

    // map setup
    GridMap::Ptr worldMap = std::make_shared<GridMap>(500, 500);
    Human::Ptr ptr = std::make_shared<Human>("adam");
    worldMap->addActor(ptr, 0, 0);

    std::cout << "UI init" << std::endl;

    // ui setup
    UserInterface::Ptr ui = std::make_shared<UserInterface>(worldMap);

    std::cout << "Loop" << std::endl;

    // set background to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    do {
        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT);

        // update dynamic uniforms
        glUniform1f(mouseXUniform, mouseX);
        glUniform1f(mouseYUniform, mouseY);

        // update ui
        ui->update(keys, mouseX, mouseY, mouseScroll, renderer);

        // resize renderer/camera if necessary
        if (GameRunner::resized) {
            renderer->resize(screenWidth, screenHeight);
            GameRunner::resized = false;
        }

        // reset mouse wheel position
        mouseScroll = 0.0f;

        // update map
        updateMap(worldMap);

        // add tile mesh model for each world entity
        renderer->getMeshObject("tile")->models.clear();
        for (const auto &entity: worldMap->getEntities()) {
            if (renderer->getCamera()
                    ->inSight(entity->getPosition())) {
                renderer->getMeshObject("tile")
                        ->models.push_back(entity->getModel(renderer->getTileSize()));
            }
        }

        // render
        renderer->render(mvpUniform);

        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    renderer->cleanup();
}

void GameRunner::updateMap(const GridMap::Ptr &map) {
    for (const WorldActor::Ptr &actor: map->getActors()) {
        WorldActor::Action act = actor->update(map);
    }
}

void GameRunner::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
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

void GameRunner::cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}

void GameRunner::characterCallback(GLFWwindow *window, unsigned int codepoint) {}

void GameRunner::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    mouseScroll = yoffset;
}

void GameRunner::resizeCallback(GLFWwindow *window, int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
    GameRunner::resized = true;
}
