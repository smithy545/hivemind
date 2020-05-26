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
    Renderer::Ptr renderer = std::make_shared<Renderer>("renderer.json");
    screenWidth = renderer->getWidth();
    screenHeight = renderer->getHeight();
    GLFWwindow *window = renderer->init();

    std::cout << "State init" << std::endl;
    state = std::make_shared<State>();
    state->setCamera(std::make_shared<Camera>(0, 0, renderer->getWidth(), renderer->getHeight()));
    state->setMap(std::make_shared<GridMap>(0, 0, 10, 9));

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
    Interface::Ptr ui = std::make_shared<Interface>("ui.json");

    std::cout << "Physics init" << std::endl;
    Collider::Ptr collider = std::make_shared<Collider>();
    Integrator::Ptr integrator = std::make_shared<Integrator>();

    std::cout << "Loop start" << std::endl;
    state->start();
    do {
        // timekeeping
        state->enterFrame();

        glClear(GL_COLOR_BUFFER_BIT);

        // resize if flag set
        if (resized) {
            renderer->resize(screenWidth, screenHeight);
            resized = false;
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
