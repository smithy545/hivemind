//
// Created by philip on 1/24/20.
//

#ifndef HIVEMIND_GAMERUNNER_H
#define HIVEMIND_GAMERUNNER_H

#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/ui/UserInterface.h"
#include "src/world/GridMap.h"


class GameRunner {
public:
    static void loop();

private:
    static bool keys[GLFW_KEY_LAST];
    static float mouseX;
    static float mouseY;
    static float mouseScroll;

    // input callbacks
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

    static void characterCallback(GLFWwindow *window, unsigned int codepoint);

    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    // game state functions
    static void updateMap(const GridMap::Ptr &map);
};


#endif //HIVEMIND_GAMERUNNER_H
