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
#include "Camera.h"

using namespace glm;


class GameRunner {
public:
    static void loop(const std::vector<GridMap::Ptr> &loadedMaps);

private:
    static Camera::Ptr camera;
    static GLFWwindow *window;
    static bool keys[256];

    static void renderMesh(const Mesh::Ptr& mesh);
    static void update(const GridMap::Ptr &map);
    static void resize(GLFWwindow *window, int width, int height);
};


#endif //HIVEMIND_GAMERUNNER_H
