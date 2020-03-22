//
// Created by philip on 1/24/20.
//

#include "GameRunner.h"

#include <iostream>
#include <memory>

#include <render/Renderer.h>
#include <world/Human.h>
#include <world/Prop.h>
#include <common/PlainEntity.h>


// static members
bool GameRunner::keys[];
int GameRunner::screenWidth = 0;
int GameRunner::screenHeight = 0;
float GameRunner::mouseX = 0;
float GameRunner::mouseY = 0;
float GameRunner::mouseScroll = 0;
bool GameRunner::resized = false;
unsigned int WorldEntity::GLOBAL_ID = 0;

void GameRunner::loop() {

    std::cout << "Renderer init" << std::endl;
    Renderer::Ptr renderer = std::make_shared<Renderer>("manifest.json");
    screenWidth = renderer->getWidth();
    screenHeight = renderer->getHeight();
    GLFWwindow *window = renderer->init();


    std::cout << "Window init" << std::endl;
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Setup keyboard inputs
    for (bool &key : keys)
        key = false;
    glfwSetKeyCallback(window, keyCallback);
    // Setup mouse inputs
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
    // Setup text input
    glfwSetCharCallback(window, characterCallback);
    // Window resize
    glfwSetFramebufferSizeCallback(window, resizeCallback);


    std::cout << "Shader init" << std::endl;
    // activate default shader program and setup uniforms
    GLuint defaultShader = renderer->getShader("default");
    glUseProgram(defaultShader);
    GLint mvpUniform = glGetUniformLocation(defaultShader, "MVP");
    GLint mouseXUniform = glGetUniformLocation(defaultShader, "mouseX");
    GLint mouseYUniform = glGetUniformLocation(defaultShader, "mouseY");
    GLint texUniform = glGetUniformLocation(defaultShader, "tex");
    glUniform1i(texUniform, 0);

    std::cout << "Map init" << std::endl;
    GridMap::Ptr worldMap = std::make_shared<GridMap>(500, 500);
    Human::Ptr eve = std::make_shared<Human>("eve");
    Structure::Ptr house = std::make_shared<Structure>();
    Prop::Ptr prop = std::make_shared<Prop>("tree");
    worldMap->addActor(eve, 0, 0);
    worldMap->placeStructure(house, 1, 1, 1, 1);
    worldMap->addEntity(prop, 1, 2);


    std::cout << "UI init" << std::endl;
    UserInterface::Ptr ui = std::make_shared<UserInterface>(worldMap);


    std::cout << "Misc init/loop start" << std::endl;
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
        ui->update(keys, mouseX, mouseY, mouseScroll, renderer->getCamera(), renderer->getTileSize());

        // resize renderer/camera if necessary
        if (GameRunner::resized) {
            renderer->resize(screenWidth, screenHeight);
            GameRunner::resized = false;
        }

        // reset mouse wheel position
        mouseScroll = 0.0f;

        // update map
        updateMap(worldMap);

        // render map
        renderer->renderMap(worldMap, "default", mvpUniform, texUniform);

        // render ui
        renderer->renderUI(ui, "default", mvpUniform, texUniform);

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
        // do something here
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
