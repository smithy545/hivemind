//
// Created by philip on 1/24/20.
//

#include "GameRunner.h"

#include <iostream>
#include <memory>
#include <unordered_map>
#include <glm/ext.hpp>

#include "src/render/Renderer.h"
#include "src/pathing/MapNode.h"
#include "src/world/Human.h"
#include "src/pathing/Pather.h"


// static members
bool GameRunner::keys[];
float GameRunner::mouseX = 0.0f;
float GameRunner::mouseY = 0.0f;
UserInterface::Ptr GameRunner::ui = nullptr;
unsigned int WorldEntity::GLOBAL_ID = 0;

void GameRunner::loop() {
    Renderer renderer(800, 600, 32);

    // init renderer and get created window
    GLFWwindow *window = renderer.init().get();

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Setup keyboard inputs
    glfwSetKeyCallback(window, keyCallback);
    // Setup mouse inputs
    glfwSetCursorPosCallback(window, cursorPosCallback);
    // Setup text input
    glfwSetCharCallback(window, characterCallback);

    // setup default shader and use for uniforms
    GLuint defaultShader = renderer.loadShaderProgram(
            "default",
            "vertex.shader",
            "fragment.shader"
    );

    // activate shader program and setup uniforms
    glUseProgram(defaultShader);
    GLint mvpUniform = glGetUniformLocation(defaultShader, "MVP");
    GLdouble mouseXUniform = glGetUniformLocation(defaultShader, "mouseX");
    GLdouble mouseYUniform = glGetUniformLocation(defaultShader, "mouseY");

    // map setup
    GridMap::Ptr worldMap = std::make_shared<GridMap>(500, 500);

    // first there was adam and he was added to the map actors
    Human::Ptr adam = std::make_shared<Human>("adam");
    worldMap->addActor(adam, 0, 20);
    for (int i = 0; i < 10; i++)
        worldMap->addActor(std::make_shared<Human>("eve" + std::to_string(i)), i, i);
    for (int i = 0; i < 10; i++)
        worldMap->placeStructure(std::make_shared<Structure>(nullptr), i + 1, i, 1, 1);

    // ui setup
    ui = std::make_shared<UserInterface>();

    // set background to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    Mesh::Ptr mesh = std::make_shared<Mesh>();
    float ts = renderer.getTileSize();
    mesh->vertices.push_back(0.f);
    mesh->vertices.push_back(0.f);

    mesh->vertices.push_back(ts);
    mesh->vertices.push_back(0.f);

    mesh->vertices.push_back(0.f);
    mesh->vertices.push_back(ts);

    mesh->vertices.push_back(ts);
    mesh->vertices.push_back(ts);

    mesh->indices.push_back(0);
    mesh->indices.push_back(1);
    mesh->indices.push_back(2);

    mesh->indices.push_back(1);
    mesh->indices.push_back(2);
    mesh->indices.push_back(3);

    mesh->reload();

    MeshObject::Ptr defaultObj = std::make_shared<MeshObject>(mesh);

    std::vector<MeshObject::Ptr> MOs;
    MOs.push_back(defaultObj);
    do {
        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT);

        // update dynamic uniforms
        glUniform1f(mouseXUniform, mouseX);
        glUniform1f(mouseYUniform, mouseY);

        float h = renderer.getHeight();
        // move adam to mouse pointer
        int mx = mouseX / (1. * ts);
        int my = (h - mouseY) / (1. * ts);
        int gridWidth = worldMap->getWidth();
        int gridHeight = worldMap->getHeight();
        int gridX = mx < gridWidth ? mx : gridWidth - 1;
        int gridY = my < gridHeight ? my : gridHeight - 1;
        if ((gridX != adam->getPosition()->getX() || gridY != adam->getPosition()->getY()) && adam->getPath().empty()) {
            MapNode::MapPath path = Pather::genAStarPath(adam->getPosition(),
                                                         worldMap->getNode(gridX, gridY));
            for (const auto &step: path) {
                adam->addToPath(step);
            }
        }
        update(worldMap);
        defaultObj->models.clear();
        for (const auto &entity: worldMap->getEntities()) {
            defaultObj->models.push_back(
                    glm::translate(
                            glm::mat4(1),
                            glm::vec3(
                                    ts * entity->getPosition()->getX(),
                                    ts * entity->getPosition()->getY(), 0)));
        }

        // render
        renderer.render(MOs, mvpUniform);

        // glfw: swap buffers and poll IO events
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    renderer.cleanup();
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

void GameRunner::update(const GridMap::Ptr &map) {
    for (const WorldActor::Ptr &actor: map->getActors()) {
        WorldActor::Action act = actor->update(map);
    }
}
