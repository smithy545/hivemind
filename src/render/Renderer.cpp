//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <glm/ext.hpp>
#include <iostream>
#include <fmt/format.h>
#include <utility>
#include <util/FileUtil.h>
#include <util/SpriteUtil.h>
#include <util/RenderUtil.h>


Renderer::Renderer(std::string configPath) : configPath(std::move(configPath)), window(nullptr) {}


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
    // read config
    auto config = FileUtil::readJsonFile(configPath);
    tileSize = config["tileSize"];
    width = config["width"];
    height = config["height"];

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

    // shaders
    for (const auto &shader: config["shaders"].items()) {
        std::cout << fmt::format("Loading shader \"{0}\" from {1} {2} ", shader.key(), shader.value()[0],
                                 shader.value()[1])
                  << std::endl;
        loadShader(shader.key(), shader.value()[0], shader.value()[1]);
    }

    // image textures
    for (const auto &tex: config["textures"].items()) {
        std::cout << fmt::format("Loading texture \"{0}\" from {1}", tex.key(), tex.value()) << std::endl;
        loadTexture(tex.key(), tex.value());
    }

    // tilesheet textures
    for (const auto &tilesheet: config["tilesheets"].items()) {
        std::cout << fmt::format("Loading tilesheet from {0}", tilesheet.value()) << std::endl;
        loadTileSheet(tilesheet.key(), tilesheet.value(), 16, 1);
    }

    // sprites
    for (const auto &sprite: config["sprites"]) {
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

void Renderer::render() {
    glUseProgram(currentShaderProgram);
    glm::mat4 viewProj = glm::ortho(0.f, 1.f * width, 0.f, 1.f * height);

    // insert map rendering here
    for (const auto &entity: loadedSprites) {
        for (auto e: entity.second->getChildren()) {
            // TODO: Add switch case for render types (e.g. "texture", "sprite", "tile" etc.)
            int x = e.second["x"];
            int y = e.second["y"];

            Sprite::Ptr sprite = entity.second->getSprite();
            glm::mat4 mvpMatrix = viewProj * glm::translate(glm::mat4(1), glm::vec3(x, y, 0));
            glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvpMatrix[0][0]);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, loadedTextures[sprite->texture]);

            glBindVertexArray(sprite->vertexArrayId);
            glDrawElements(GL_TRIANGLES, sprite->indices.size(), GL_UNSIGNED_INT, nullptr);
        }
    }
}

void Renderer::render(const Camera::Ptr &camera) {
    glUseProgram(currentShaderProgram);
    glm::mat4 viewProj = camera->getViewProjectionMatrix();

    // insert map rendering here
    for (const auto &entity: loadedSprites) {
        for (auto e: entity.second->getChildren()) {
            int x = e.second["x"];
            int y = e.second["y"];

            Sprite::Ptr sprite = entity.second->getSprite();
            glm::mat4 mvpMatrix = viewProj * glm::translate(glm::mat4(1), glm::vec3(x, y, 0));
            glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvpMatrix[0][0]);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, loadedTextures[sprite->texture]);

            glBindVertexArray(sprite->vertexArrayId);
            glDrawElements(GL_TRIANGLES, sprite->indices.size(), GL_UNSIGNED_INT, nullptr);
        }
    }
}

void Renderer::resize(int width, int height) {
    this->width = width;
    this->height = height;
}

void Renderer::setShader(const std::string &name) {
    if (loadedShaders.find(name) != loadedShaders.end()) {
        currentShaderProgram = loadedShaders[name];
        glUseProgram(currentShaderProgram);
        mvpUniform = glGetUniformLocation(currentShaderProgram, "MVP");
        texUniform = glGetUniformLocation(currentShaderProgram, "tex");
        glUniform1i(texUniform, 0);
    } else {
        std::cerr << "No shader found with name " << name << std::endl;
    }
}

void Renderer::loadShader(const std::string &name, const std::string &vertexShaderPath,
                          const std::string &fragmentShaderPath) {
    loadedShaders[name] = RenderUtil::loadShaderProgram(vertexShaderPath, fragmentShaderPath);
}

void Renderer::loadSprite(const std::string &path) {
    std::string name;
    auto sprite = SpriteUtil::generateSpriteFromJson(path, name);
    loadedSprites[name] = std::make_shared<SpritePrototype>(sprite);
}

void Renderer::loadTexture(const std::string &name, const std::string &texturePath) {
    int w, h;
    loadedTextures[name] = RenderUtil::loadTexture(texturePath, w, h);
}

void Renderer::loadTileSheet(const std::string &name, const std::string &path, int sheetTileSize, int padding) {
    int w, h;
    loadedTextures[name] = RenderUtil::loadTexture(path, w, h);
    int i = 0;
    double contentSize = sheetTileSize - 2 * padding;
    float uStep = contentSize / (1.0 * w);
    float vStep = contentSize / (1.0 * h);
    float uPadding = (1.0 * padding) / (1.0 * w);
    float vPadding = (1.0 * padding) / (1.0 * h);
    float v = vPadding;
    for (int y = 0; y < h; y += sheetTileSize) {
        float u = uPadding;
        for (int x = 0; x < w; x += sheetTileSize) {
            Sprite::Ptr sprite = std::make_shared<Sprite>();

            sprite->texture = name;

            // bottom left
            sprite->vertices.push_back(0);
            sprite->vertices.push_back(0);

            sprite->uvs.push_back(u);
            sprite->uvs.push_back(-v);

            // bottom right
            sprite->vertices.push_back(contentSize);
            sprite->vertices.push_back(0);

            sprite->uvs.push_back(u + uStep);
            sprite->uvs.push_back(-v);

            // top right
            sprite->vertices.push_back(contentSize);
            sprite->vertices.push_back(contentSize);

            sprite->uvs.push_back(u + uStep);
            sprite->uvs.push_back(-v - vStep);

            // top left
            sprite->vertices.push_back(0);
            sprite->vertices.push_back(contentSize);

            sprite->uvs.push_back(u);
            sprite->uvs.push_back(-v - vStep);

            // indices
            sprite->indices.push_back(0);
            sprite->indices.push_back(2);
            sprite->indices.push_back(3);

            sprite->indices.push_back(1);
            sprite->indices.push_back(2);
            sprite->indices.push_back(0);

            sprite->reload();
            loadedSprites[fmt::format("{0}_tile_{1}", name, i)] = std::make_shared<SpritePrototype>(sprite);

            u += uStep + 2 * uPadding;
            i++;
        }
        v += vStep + 2 * vPadding;
    }
}

void Renderer::move(const std::string &spriteName, unsigned int id, int x, int y) {
    if (loadedSprites.find(spriteName) != loadedSprites.end()
        && loadedSprites[spriteName]->get(id) != nullptr) {
        loadedSprites[spriteName]->set(id, "x", x);
        loadedSprites[spriteName]->set(id, "y", y);
    }
}

unsigned int Renderer::add(const std::string &spriteName, int x, int y) {
    if (loadedSprites.find(spriteName) != loadedSprites.end()) {
        json obj = {{"x", x},
                    {"y", y}};
        return loadedSprites[spriteName]->generate(obj);
    }
    std::cerr << "No sprite found at " << spriteName << std::endl;
}

void Renderer::destroy(const std::string &spriteName, unsigned int id) {
    if (loadedSprites.find(spriteName) != loadedSprites.end())
        loadedSprites[spriteName]->destroy(id);
}