#include <chrono>
#include <iostream>
#include <thread>

#include "engine/State.h"
#include "collision/Collider.h"
#include "collision/Integrator.h"
#include "engine/Interface.h"
#include "render/Renderer.h"


// window state
static int screen_width;
static int screen_height;
static bool resized;
static bool enforce_fps = false;
static int desired_fps = 100;

// game state
static State::Ptr state;

// game update method
void loop();

int main() {
    std::cout << "Begin Society" << std::endl;
    std::thread game(loop);
    game.join();
    std::cout << "End." << std::endl;
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
    std::cout << "Renderer init" << std::endl;
    Renderer renderer;
    GLFWwindow *window = renderer.init("renderer.json");
    screen_width = renderer.get_width();
    screen_height = renderer.get_height();

    std::cout << "State init" << std::endl;
    state = std::make_shared<State>(screen_width, screen_height);
    auto god = std::make_shared<God>();
    auto scene = std::make_shared<Scene>(renderer.get_width(), renderer.get_height());

    // setup some boxes
    auto box_mesh = Renderer::generate_box_mesh_triangles(1, 2, 3, glm::vec4(1.0f, 0.f, 0.f, 1.0f));
    auto outline_mesh =  Renderer::generate_box_mesh_lines(1, 2, 3, glm::vec4(0.0f, 0.f, 0.f, 1.0f));
    for(auto x = 0; x < 10; x++) {
        for(auto z = 0; z < 10; z++) {
            auto body = std::make_shared<PhysicsBody>();
            body->set_origin({x, 10, z});
            scene->add_to_scene("instanced_color", box_mesh, body);
            scene->add_to_scene("instanced_color", outline_mesh, body);
            god->add(body);
        }
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
    Interface::Ptr ui = std::make_shared<Interface>(scene, god);

    std::cout << "Physics init" << std::endl;
    Collider::Ptr collider = std::make_shared<Collider>();
    Integrator::Ptr integrator = std::make_shared<Integrator>();

    std::cout << "Loop start" << std::endl;
    state->start();
    do {
        // timekeeping
        auto dt = state->enter_frame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (resized) {
            renderer.resize(screen_width, screen_height);
            scene->get_camera()->resize(screen_width, screen_height);
            resized = false;
        }

        if (!state->is_paused()) {
            // check collisions and update bodies
            if (collider != nullptr && integrator != nullptr) {
                auto updated = collider->update(god->get_collision_tree());
                integrator->update(updated, 1.0f);
            }
        }

        // update state with user input
        ui->update(state, scene, god);
        god->update();

        // enforce fps if desired
        auto fps = state->get_fps();
        if(enforce_fps && (fps - desired_fps > 1.0)) {
            std::chrono::duration<double> remaining{2*(fps-desired_fps)/(fps*desired_fps)};
            std::this_thread::sleep_for(remaining);
        }

        // render
        renderer.render(scene->get_render_head(), scene->get_camera());

        // reset mouse wheel position
        state->set_mouse_scroll(0.0f);

        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 &&
            !state->is_stopped());

    // cleanup state before cleaning up renderer so glfw isn't terminated
    scene->cleanup();
    renderer.cleanup();
}
