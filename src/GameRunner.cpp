//
// Created by philip on 1/24/20.
//

#include "GameRunner.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "src/render/Renderer.h"
#include "src/pathing/MapNode.h"
#include "src/world/Human.h"
#include "src/pathing/Pather.h"


// static members
bool GameRunner::keys[];
float GameRunner::mouseX = 0.0f;
float GameRunner::mouseY = 0.0f;
UserInterface::Ptr GameRunner::ui = nullptr;
int MapEntity::GLOBAL_ID = 1;


void GameRunner::loop() {
    Renderer renderer(800, 600, 32);
    float w = renderer.getWidth();
    float h = renderer.getHeight();
    float ts = renderer.getTileSize();

    GLFWwindow *window = renderer.init();
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Setup keyboard inputs
    glfwSetKeyCallback(window, keyCallback);
    // Setup mouse inputs
    glfwSetCursorPosCallback(window, cursorPosCallback);
    // Setup text input
    glfwSetCharCallback(window, characterCallback);

    GLuint defaultShader = renderer.loadShaderProgram("default", "vertex.shader", "fragment.shader");

    // activate shader program and setup uniforms
    glUseProgram(defaultShader);
    GLdouble mouseXUniform = glGetUniformLocation(defaultShader, "mouseX");
    GLdouble mouseYUniform = glGetUniformLocation(defaultShader, "mouseY");
    GLint widthUniform = glGetUniformLocation(defaultShader, "width");
    GLint heightUniform = glGetUniformLocation(defaultShader, "height");

    // set constant uniforms
    glUniform1f(widthUniform, ts / w);
    glUniform1f(heightUniform, ts / h);

    // set background to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // setup non opengl entites
    // map setup
    std::vector<GridMap::Ptr> loadedMaps;
    loadedMaps.push_back(std::make_shared<GridMap>(500, 500));

    // first there was adam and he was added to the map actors
    Human::Ptr adam = std::make_shared<Human>("adam");
    loadedMaps[0]->addActor(adam, 0, 20);
    for (int i = 0; i < 10; i++)
        loadedMaps[0]->addActor(std::make_shared<Human>("eve" + std::to_string(i)), i, i);
    for (int i = 0; i < 10; i++)
        loadedMaps[0]->placeStructure(std::make_shared<Structure>(nullptr), i + 1, i, 1, 1);

    // ui setup
    ui = std::make_shared<UserInterface>();

    do {
        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT);

        // update dynamic uniforms
        glUniform1f(mouseXUniform, mouseX);
        glUniform1f(mouseYUniform, mouseY);

        // move adam to mouse pointer
        int mx = mouseX / ts;
        int my = (h - mouseY) / ts;
        int gridWidth = loadedMaps[0]->getWidth();
        int gridHeight = loadedMaps[0]->getHeight();
        int gridX = mx < gridWidth ? mx : gridWidth - 1;
        int gridY = my < gridHeight ? my : gridHeight - 1;
        if ((gridX != adam->getMapNode()->getX() || gridY != adam->getMapNode()->getY()) && adam->getPath().empty()) {
            MapNode::MapPath path = Pather::genAStarPath(adam->getMapNode(),
                                                         loadedMaps[0]->getNode(gridX, gridY));
            for (const auto &step: path) {
                adam->addToPath(step);
            }
        }

        // update and render all maps
        for (const GridMap::Ptr &map: loadedMaps) {
            update(map);

            // determine which entities are visible
            for (const MapEntity::Ptr &entity: map->getEntities()) {
                if (renderer.getCamera()->inSight(entity->getMapNode())) {
                    map->markForRendering(entity);
                }
            }
            // TODO: Figure out why tilesize has to be doubled to work properly
            Renderer::renderMesh(map->generateMesh(w, h, 2 * ts));
        }
        // render ui
        //Renderer::renderMesh(ui->generateMesh(w, h, 2 * ts));

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

void GameRunner::update(const GridMap::Ptr &map) {
    for (const MapActor::Ptr &actor: map->getActors()) {
        switch (actor->update(map)) {
            case MapActor::MOVE:
                // do something I guess
                break;
            case MapActor::IDLE:
                // std::cout << "Actor " << actor->getUId() << " idling" << std::endl;
                break;
        }
    }
}
