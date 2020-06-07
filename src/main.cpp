#include <iostream>
#include <thread>

#include "engine/State.h"
#include "engine/Collider.h"
#include "engine/Integrator.h"
#include "engine/Interface.h"
#include "pathing/GridMap.h"
#include "render/Renderer.h"


// window state
static int screenWidth;
static int screenHeight;
static bool resized;

// game state
static State::Ptr state;

// game update method
void loop();

int main() {
    std::cout << "Begin Society" << std::endl;
    std::thread gameThread(loop);
    gameThread.join();
    std::cout << "End." << std::endl;

    return 0;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
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

void characterCallback(GLFWwindow *window, unsigned int codepoint) {}

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    state->setMouseX(xpos);
    state->setMouseY(ypos);
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    state->setMouseScroll(yoffset);
}

void resizeCallback(GLFWwindow *window, int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
    resized = true;
}

void loop() {
    std::cout << "Renderer init" << std::endl;
    Renderer::Ptr renderer = std::make_shared<Renderer>();
    screenWidth = renderer->getWidth();
    screenHeight = renderer->getHeight();
    GLFWwindow *window = renderer->init("renderer.json");

    std::cout << "State init" << std::endl;
    state = std::make_shared<State>(renderer->getWidth(), renderer->getHeight());
    state->setMap(std::make_shared<GridMap>(0, 0, 64, 64));
    state->getScene().getCamera()->setPosition({0,2,10});

    // generate boxes
    auto box = renderer->generateBoxMeshTriangles(1, 2, 3, glm::vec4(1.0f, 0.f, 0.f, 1.0f));
    auto outline = renderer->generateBoxMeshLines(1, 2, 3, glm::vec4(0.0f, 0.f, 0.f, 1.0f));
    for(int y = 0; y < 10; y++) {
        // only set physics on outline since the box and outline share a body
        auto body = std::make_shared<Body>();
        body->setOrigin({y,10*y,0});
        state->getScene().addToScene("color", box, body, false);
        state->getScene().addToScene("color", outline, body, true);
    }

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
    // disable cursor to enable automatic recentering
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // clear background to black
    glClearColor(1.0f,1.0f, 1.0f, 1.0f);

    std::cout << "UI init" << std::endl;
    Interface::Ptr ui = std::make_shared<Interface>();

    std::cout << "Physics init" << std::endl;
    Collider::Ptr collider = std::make_shared<Collider>();
    Integrator::Ptr integrator = std::make_shared<Integrator>(1.0);

    std::cout << "Loop start" << std::endl;
    state->start();
    do {
        // timekeeping
        state->enterFrame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto scene = state->getScene();
        // resize if flag set
        if (resized) {
            renderer->resize(screenWidth, screenHeight);
            scene.getCamera()->resize(screenWidth, screenHeight);
            resized = false;
        }
        if (!state->isPaused()) {
            // check collisions and update bodies
            if (collider != nullptr && integrator != nullptr) {
                auto updatedBodies = collider->update(scene.getCollisionTree());
                integrator->update(updatedBodies);
            }
        }

        // update state with user input
        ui->update(state);

        // render
        renderer->render(scene.getRenderTree(), scene.getCamera());

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
