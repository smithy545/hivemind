//
// Created by philip on 1/24/20.
//

#include "GameRunner.h"

#include <iostream>
#include <memory>

#include "render/Renderer.h"
#include "world/Human.h"
#include "world/Prop.h"


// static members
bool GameRunner::keys[];
int GameRunner::screenWidth = 1200;
int GameRunner::screenHeight = 900;
float GameRunner::mouseX = 0;
float GameRunner::mouseY = 0;
float GameRunner::mouseScroll = 0;
bool GameRunner::resized = false;
unsigned int WorldEntity::GLOBAL_ID = 0;

const std::string &WorldEntity::getSpriteName() const {
    return spriteName;
}

void WorldEntity::setSpriteName(const std::string &spriteName) {
    WorldEntity::spriteName = spriteName;
}


void GameRunner::loop() {
    std::cout << "Renderer init" << std::endl;
    Renderer::Ptr renderer = std::make_shared<Renderer>(screenWidth, screenHeight);
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

    // activate default shader program and setup uniforms
    std::cout << "Shader init" << std::endl;
    GLuint defaultShader = renderer->getShader("default");
    glUseProgram(defaultShader);
    GLint mvpUniform = glGetUniformLocation(defaultShader, "MVP");
    GLint mouseXUniform = glGetUniformLocation(defaultShader, "mouseX");
    GLint mouseYUniform = glGetUniformLocation(defaultShader, "mouseY");
    GLint texUniform = glGetUniformLocation(defaultShader, "tex");

    std::cout << "Map init" << std::endl;
    GridMap::Ptr worldMap = std::make_shared<GridMap>(500, 500);
    Human::Ptr eve = std::make_shared<Human>("eve");
    Structure::Ptr house = std::make_shared<Structure>();
    Prop::Ptr prop = std::make_shared<Prop>("d");
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

        // refresh mesh model for each world entity
        for (const auto &entity: worldMap->getEntities()) {
            auto spriteObj = renderer->getSprite(entity->getSpriteName());
            if (spriteObj == nullptr) {
                std::cerr << "No loaded mesh found for " << entity->getSpriteName() << std::endl;
            } else if (renderer->getCamera()->inSight(entity->getPosition(), renderer->getTileSize())) {
                spriteObj->models.push_back(entity->getModel(renderer->getTileSize()));
            }
        }

        // render
        renderer->renderSprites("default", mvpUniform, texUniform);

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
