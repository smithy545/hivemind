//
// Created by philip on 1/24/20.
//

#include "GameRunner.h"

#include <iostream>
#include <memory>
#include <render/Renderer.h>

#include "PhysicsCollider.h"
#include "PhysicsIntegrator.h"
#include "UserInterface.h"


// static members
int GameRunner::screenWidth = 0;
int GameRunner::screenHeight = 0;
bool GameRunner::resized = false;
GameState::Ptr GameRunner::state = nullptr;
const std::string GameRunner::RENDERER_CONFIG_FILE = "json/renderer.json";
const std::string GameRunner::UI_CONFIG_FILE = "json/ui.json";

void GameRunner::loop() {
    std::cout << "Renderer init" << std::endl;
    Renderer::Ptr renderer = std::make_shared<Renderer>(RENDERER_CONFIG_FILE);
    screenWidth = renderer->getWidth();
    screenHeight = renderer->getHeight();
    GLFWwindow *window = renderer->init();

    std::cout << "State init" << std::endl;
    state = std::make_shared<GameState>();
    state->setCamera(std::make_shared<Camera>(0, 0, renderer->getWidth(), renderer->getHeight()));

    std::cout << "Window init" << std::endl;
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Setup keyboard inputs
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCharCallback(window, characterCallback);
    // Setup mouse inputs
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    // Window resize
    glfwSetFramebufferSizeCallback(window, resizeCallback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    std::cout << "UI init" << std::endl;
    UserInterface::Ptr ui = std::make_shared<UserInterface>(UI_CONFIG_FILE);

    std::cout << "Physics init" << std::endl;
    PhysicsCollider::Ptr collider = std::make_shared<PhysicsCollider>();
    PhysicsIntegrator::Ptr integrator = std::make_shared<PhysicsIntegrator>();

    std::cout << "Loop start" << std::endl;
    state->start();
    do {
        // timekeeping
        state->enterFrame();

        glClear(GL_COLOR_BUFFER_BIT);

        // resize if flag set
        if (GameRunner::resized) {
            renderer->resize(screenWidth, screenHeight);
            GameRunner::resized = false;
        }

        // check collisions and update bodies
        if (!state->isPaused()) {
            if (collider != nullptr)
                collider->update(state);
            if (integrator != nullptr)
                integrator->update(state);
        }

        // update state with user input
        ui->update(state);

        // render
        renderer->render(state->getRenderTree(), state->getCamera());

        // reset mouse wheel position
        state->setMouseScroll(0.0f);

        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 &&
           !state->shouldStop());

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

void GameRunner::characterCallback(GLFWwindow *window, unsigned int codepoint) {}

void GameRunner::cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    state->setMouseX(xpos);
    state->setMouseY(ypos);
}

void GameRunner::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {}

void GameRunner::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    state->setMouseScroll(yoffset);
}

void GameRunner::resizeCallback(GLFWwindow *window, int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
    GameRunner::resized = true;
}
