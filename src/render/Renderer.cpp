//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <iostream>
#include <fmt/format.h>

#include "util/FileUtil.h"
#include "util/SpriteUtil.h"
#include "util/RenderUtil.h"


Renderer::Renderer(const std::string &manifestFile) : window(nullptr) {
    auto config = FileUtil::readJsonFile(manifestFile);

    width = config["width"];
    height = config["height"];
    camera = std::make_shared<Camera>(0, 0, width, height);
}

GLuint Renderer::getShader(const std::string &name) {
    return loadedShaders[name];
}

const Camera::Ptr &Renderer::getCamera() const {
    return camera;
}

int Renderer::getWidth() const {
    return width;
}

int Renderer::getHeight() const {
    return height;
}

int Renderer::getTileSize() const {
    return tileSize;
}

GLFWwindow *Renderer::init() {
    // Initialise GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "Society", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // enable srgb
    glEnable(GL_FRAMEBUFFER_SRGB);

    // cull triangles facing away from camera
    glEnable(GL_CULL_FACE);

    // TODO: Add jsonschema validation or something for more informative config errors
    auto manifest = FileUtil::readJsonFile("manifest.json");
    tileSize = manifest["tileSize"];

    // shaders
    for (const auto &shader: manifest["shaders"].items()) {
        std::cout << fmt::format("Loading shader \"{0}\" from {1} {2} ", shader.key(), shader.value()[0],
                                 shader.value()[1])
                  << std::endl;
        loadShader(shader.key(), shader.value()[0], shader.value()[1]);
    }

    // image textures
    for (const auto &tex: manifest["textures"].items()) {
        std::cout << fmt::format("Loading texture \"{0}\" from {1}", tex.key(), tex.value()) << std::endl;
        loadTexture(tex.key(), tex.value());
    }

    // sprites
    for (const auto &sprite: manifest["sprites"]) {
        std::cout << fmt::format("Loading sprite from {0}", sprite) << std::endl;
        loadSprite(sprite);
    }

    return window;
}

void Renderer::cleanup() {
    // clear loaded meshes
    loadedTextures.clear();

    // clear loaded shaders
    for (auto &shaderProgram : loadedShaders) {
        glDeleteProgram(shaderProgram.second);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources
    glfwTerminate();
}

void Renderer::render(const WorldMap::Ptr &map, const std::string &shaderName, GLint mvpUniform, GLuint texUniform) {
    if (loadedShaders.find(shaderName) == loadedShaders.end()) {
        std::cerr << fmt::format("Couldn't find shader {0} in loaded shaders", shaderName) << std::endl;
        return;
    }

    GLuint program = loadedShaders[shaderName];
    glUseProgram(program);
    glUniform1i(texUniform, 0);

    glm::mat4 viewProj = camera->getViewProjectionMatrix();
    // insert map rendering here
    for (const auto &entity: map->getEntities()) {
        // skip sprites that don't exist
        if (loadedSprites.find(entity->getSpriteName()) == loadedSprites.end())
            continue;

        Sprite::Ptr sprite = loadedSprites[entity->getSpriteName()];
        glm::mat4 mvpMatrix = viewProj * entity->getModel(tileSize);
        glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvpMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, loadedTextures[sprite->texture]);

        glBindVertexArray(sprite->vertexArrayId);
        glDrawElements(GL_TRIANGLES, sprite->indices.size(), GL_UNSIGNED_INT, nullptr);
    }
}

void Renderer::resize(int width, int height) {
    this->width = width;
    this->height = height;
    camera->resize(width, height);
}

void Renderer::loadShader(const std::string &name, const std::string &vertexShaderPath,
                          const std::string &fragmentShaderPath) {
    loadedShaders[name] = RenderUtil::loadShaderProgram(vertexShaderPath, fragmentShaderPath);
}

void Renderer::loadSprite(const std::string &spritePath) {
    std::string name;
    auto sprite = SpriteUtil::generateSpriteFromJson(spritePath, name);
    loadedSprites[name] = sprite;
}

void Renderer::loadTexture(const std::string &name, const std::string &texturePath) {
    int width, height;
    loadedTextures[name] = RenderUtil::loadTexture(texturePath, width, height);
}