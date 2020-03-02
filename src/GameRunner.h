//
// Created by philip on 1/24/20.
//

#ifndef HIVEMIND_GAMERUNNER_H
#define HIVEMIND_GAMERUNNER_H

// Include standard headers
#include <string>
#include <thread>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "src/world/GridMap.h"
#include "src/ui/UserInterface.h"


class GameRunner {
public:
    static void loop();

private:
    static bool keys[256];
    static float mouseX;
    static float mouseY;

    // input callbacks
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void characterCallback(GLFWwindow* window, unsigned int codepoint);

    // game state functions
    static void update(const GridMap::Ptr &map);
};


#endif //HIVEMIND_GAMERUNNER_H
