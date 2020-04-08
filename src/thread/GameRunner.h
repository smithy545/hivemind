//
// Created by philip on 1/24/20.
//

#ifndef SOCIETY_GAMERUNNER_H
#define SOCIETY_GAMERUNNER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <state/GameState.h>
#include <ui/UserInterface.h>
#include <unordered_map>
#include <world/GridMap.h>


class GameRunner {
public:
    static void loop();

private:
    // window state
    static int screenWidth;
    static int screenHeight;
    static bool resized;

    static GameState::Ptr readManifest(const std::string &manifestPath);

    // window callback(s)
    static void resizeCallback(GLFWwindow *window, int width, int height);

    // user input callbacks
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);

    static void characterCallback(GLFWwindow *window, unsigned int codepoint);

    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    // game state
    static GameState::Ptr state;
};


#endif //SOCIETY_GAMERUNNER_H
