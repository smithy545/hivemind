//
// Created by philip on 1/24/20.
//

#ifndef HIVEMIND_GAMERUNNER_H
#define HIVEMIND_GAMERUNNER_H

// Include standard headers
#include <thread>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include "GridMap.h"

using namespace glm;


class GameRunner {
public:
    static void loop(std::vector<GridMap::Ptr> loadedMaps);
    static void render();
    static void update(GridMap::Ptr map);
private:
    static GLFWwindow* window;
    static bool keys[256];
};


#endif //HIVEMIND_GAMERUNNER_H
