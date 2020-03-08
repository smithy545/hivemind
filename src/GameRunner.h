//
// Created by philip on 1/24/20.
//

#ifndef SOCIETY_GAMERUNNER_H
#define SOCIETY_GAMERUNNER_H

#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ui/UserInterface.h"
#include "world/GridMap.h"


class GameRunner {
public:
    static void loop();

private:
    static bool keys[GLFW_KEY_LAST];
    static int screenWidth;
    static int screenHeight;
    static float mouseX;
    static float mouseY;
    static float mouseScroll;

    // static state variables
    static bool resized;

    // input callbacks
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);

    static void characterCallback(GLFWwindow *window, unsigned int codepoint);

    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    // window callback(s)
    static void resizeCallback(GLFWwindow *window, int width, int height);

    // game state functions
    static void updateMap(const GridMap::Ptr &map);
};


#endif //SOCIETY_GAMERUNNER_H
