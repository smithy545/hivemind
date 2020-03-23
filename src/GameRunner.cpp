//
// Created by philip on 1/24/20.
//

#include "GameRunner.h"

#include <iostream>
#include <memory>
#include <render/Renderer.h>
#include <util/FileUtil.h>


// static members
int GameRunner::screenWidth = 0;
int GameRunner::screenHeight = 0;
bool GameRunner::resized = false;
GameState::Ptr GameRunner::state = nullptr;

GameState::Ptr GameRunner::readManifest(const std::string &manifestPath) {
    json config = FileUtil::readJsonFile(manifestPath);
    for (const auto &entity: config["entities"].items()) {
        if (entity.value().is_string()) {
            //loadedEntities[entity.key()] = std::make_shared<Entity>(FileUtil::readJsonFile(entity.value()));
        } else if (entity.value().is_object()) {
            //loadedEntities[entity.key()] = std::make_shared<Entity>(entity.value());
        }
    }

    // initial game state
    return std::make_shared<GameState>();
}

void GameRunner::update() {}

void GameRunner::loop() {
    // load config file and get initial game state
    std::cout << "Reading manifest" << std::endl;
    state = readManifest("manifest.json");


    std::cout << "Renderer init" << std::endl;
    Renderer::Ptr renderer = std::make_shared<Renderer>("renderer.json");
    screenWidth = renderer->getWidth();
    screenHeight = renderer->getHeight();
    GLFWwindow *window = renderer->init();


    std::cout << "Window init" << std::endl;
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
    renderer->setShader("default");

    std::cout << "UI init" << std::endl;
    UserInterface::Ptr ui = std::make_shared<UserInterface>("ui.json");

    std::cout << "Misc init/loop start" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    do {
        glClear(GL_COLOR_BUFFER_BIT);

        // resize renderer/camera if necessary
        if (GameRunner::resized) {
            renderer->resize(screenWidth, screenHeight);
            GameRunner::resized = false;
        }

        // reset mouse wheel position
        state->setMouseScroll(0.0f);

        // update ui
        ui->update(state);

        // render
        renderer->render(state);

        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    renderer->cleanup();
}


void GameRunner::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    switch (action) {
        case GLFW_PRESS:
            state->setKey(key, true);
            break;
        case GLFW_RELEASE:
            state->setKey(key, false);
            break;
        case GLFW_REPEAT:
            break;
        default:
            std::cerr << "Key action \"" << action << "\" not handled" << std::endl;
    }
}

void GameRunner::cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    state->setMouseX(xpos);
    state->setMouseY(ypos);
}

void GameRunner::characterCallback(GLFWwindow *window, unsigned int codepoint) {}

void GameRunner::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    state->setMouseScroll(yoffset);
}

void GameRunner::resizeCallback(GLFWwindow *window, int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
    GameRunner::resized = true;
}
