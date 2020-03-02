//
// Created by philip on 1/24/20.
//

#include "GameRunner.h"

#include <iostream>
#include <memory>

#include "src/render/Renderer.h"
#include "src/world/Human.h"


// static members
bool GameRunner::keys[];
float GameRunner::mouseX = 0.0f;
float GameRunner::mouseY = 0.0f;
float GameRunner::mouseScroll = 0.0f;
unsigned int WorldEntity::GLOBAL_ID = 0;

void GameRunner::loop() {
    std::cout << "Renderer init" << std::endl;

    // instantiate renderer and get created window
    Renderer::Ptr renderer = std::make_shared<Renderer>(800, 600, 32);
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


    std::cout << "Shader init" << std::endl;

    // activate shader program and setup uniforms
    GLuint defaultShader = renderer->getShader("default");
    glUseProgram(defaultShader);
    GLint mvpUniform = glGetUniformLocation(defaultShader, "MVP");
    GLdouble mouseXUniform = glGetUniformLocation(defaultShader, "mouseX");
    GLdouble mouseYUniform = glGetUniformLocation(defaultShader, "mouseY");

    std::cout << "Map init" << std::endl;

    // map setup
    GridMap::Ptr worldMap = std::make_shared<GridMap>(500, 500);

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
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    renderer->cleanup();
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

void GameRunner::cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}

void GameRunner::characterCallback(GLFWwindow *window, unsigned int codepoint) {}

void GameRunner::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    mouseScroll = yoffset;
}

void GameRunner::updateMap(const GridMap::Ptr &map) {
    for (const WorldActor::Ptr &actor: map->getActors()) {
        WorldActor::Action act = actor->update(map);
    }
}
