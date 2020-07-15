#include <chrono>
#include <iostream>
#include <thread>

#include "engine/Interface.h"
#include "pathing/GridMap.h"
#include "render/Renderer.h"


// window state
static int screen_width = 800;
static int screen_height = 600;
static bool resized;
static bool enforce_fps = false;
static double desired_dt = 1./60.;

// game state
static State::Ptr state;

// game update method
void loop();

int main() {
    std::thread game(loop);
    game.join();
    return 0;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    switch (action) {
        case GLFW_PRESS:
            state->set_key(key, true);
            break;
        case GLFW_RELEASE:
            state->set_key(key, false);
            break;
        case GLFW_REPEAT:
            break;
        default:
            std::cerr << "Key action \"" << action << "\" not handled" << std::endl;
    }
}

void characterCallback(GLFWwindow *window, unsigned int codepoint) {}

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    state->set_mouse_x(xpos);
    state->set_mouse_y(ypos);
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    state->set_mouse_scroll(yoffset);
}

void resizeCallback(GLFWwindow *window, int width, int height) {
    screen_width = width;
    screen_height = height;
    glViewport(0, 0, width, height);
    resized = true;
}

void loop() {
    std::cout << "State init" << std::endl;
    state = std::make_shared<State>(screen_width, screen_height);
    God god;

    std::cout << "Window init" << std::endl;
    Renderer renderer;
    GLFWwindow *window = renderer.init("renderer.json", screen_width, screen_height);
    Camera camera(screen_width, screen_height);

    // must be init after render.init()
    auto map = std::make_shared<GridMap>(64, 64);
    Interface ui;

    std::cout << "Input init" << std::endl;
    // Setup keyboard inputs
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCharCallback(window, characterCallback);
    // Setup mouse inputs
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    // Window resize
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    std::cout << "Loop start" << std::endl;
    state->start();
    do {
        // timekeeping
        auto dt = state->enter_frame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (resized) {
            camera.resize(screen_width, screen_height);
            resized = false;
        }

        // update state with user input
        ui.update(state, camera);
        god.update();

        // reset mouse wheel position
        state->set_mouse_scroll(0.0f);

        // render
        renderer.render(camera, map);

        // enforce fps if desired
        if(enforce_fps && dt < desired_dt)
            std::this_thread::sleep_for(std::chrono::duration<double>(desired_dt - dt));

        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 &&
            !state->is_stopped());

    // cleanup state before cleaning up renderer so glfw isn't terminated
    renderer.cleanup();
}
