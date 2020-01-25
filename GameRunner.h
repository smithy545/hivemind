//
// Created by philip on 1/24/20.
//

#ifndef HIVEMIND_GAMERUNNER_H
#define HIVEMIND_GAMERUNNER_H

// Include standard headers
#include <thread>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;


class GameRunner {
public:
    static void loop();
private:
    static GLFWwindow* window;
    static bool* keys;
};


#endif //HIVEMIND_GAMERUNNER_H
