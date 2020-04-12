//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <iostream>
#include <fmt/format.h>
#include <utility>
#include <util/FileUtil.h>
#include <util/SpriteUtil.h>
#include <util/RenderUtil.h>


const std::string Renderer::CONFIG_WIDTH_KEY = "width";
const std::string Renderer::CONFIG_HEIGHT_KEY = "height";
const std::string Renderer::CONFIG_SPRITESHEETS_KEY = "spriteSheets";
const std::string Renderer::CONFIG_TILESHEETS_KEY = "tileSheets";
const std::string Renderer::CONFIG_TILESIZE_KEY = "tileSize";
const std::string Renderer::CONFIG_TEXTURES_KEY = "textures";
const std::string Renderer::CONFIG_SHADERS_KEY = "shaders";


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
    tileSize = config[CONFIG_TILESIZE_KEY];
    width = config[CONFIG_WIDTH_KEY];
    height = config[CONFIG_HEIGHT_KEY];

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
    for (const auto &shader: config[CONFIG_SHADERS_KEY].items()) {
        std::cout << fmt::format("Loading shader \"{0}\" from {1} {2} ", shader.key(), shader.value()[0],
                                 shader.value()[1])
                  << std::endl;
        loadShader(shader.key(), shader.value()[0], shader.value()[1]);
    }

    // image textures
    for (const auto &tex: config[CONFIG_TEXTURES_KEY].items()) {
        std::cout << fmt::format("Loading texture \"{0}\" from {1}", tex.key(), tex.value()) << std::endl;
        loadTexture(tex.key(), tex.value());
    }

    // tilesheet textures
    for (const auto &tilesheet: config[CONFIG_TILESHEETS_KEY]) {
        std::cout << fmt::format("Loading tilesheet from {0}", tilesheet) << std::endl;
        loadTileSheet(tilesheet);
    }

    // sprites
    for (const auto &sprite: config[CONFIG_SPRITESHEETS_KEY]) {
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

void Renderer::render(const GameState::Ptr &state) {
    glUseProgram(currentShaderProgram);
    glm::mat4 viewProj = state->getCamera()->getViewProjectionMatrix();

    // insert map rendering here
    for (const auto &entity: state->getWorldEntities()) {}
    for (const auto &entity: state->getUiEntities()) {}

    /*
    for(auto entity : entities->getChildren()) {
        int x = entity.second["x"];
        int y = entity.second["y"];

        Sprite::Ptr sprite = loadedSprites[entity.second["spriteName"]];
        glm::mat4 mvpMatrix = viewProj * glm::translate(glm::mat4(1), glm::vec3(x, y, 0));
        glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvpMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, loadedTextures[sprite->texture]);

        glBindVertexArray(sprite->vertexArrayId);
        glDrawElements(GL_TRIANGLES, sprite->indices.size(), GL_UNSIGNED_INT, nullptr);
    }*/
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
    loadedSprites[name] = SpriteUtil::generateSpriteFromJson(fmt::format("json/spritesheets/{}", path), name);
}

void Renderer::loadTexture(const std::string &name, const std::string &texturePath) {
    int w, h;
    loadedTextures[name] = RenderUtil::loadTexture(texturePath, w, h);
}

void Renderer::loadTileSheet(const std::string &path) {
    int w, h;
    auto tilesheet = FileUtil::readJsonFile(fmt::format("json/tilesheets/{}", path));
    // TODO: add constants for tilesheet keys
    std::string name = tilesheet["name"];
    int sheetTileSize = tilesheet["tileSize"];
    int padding = tilesheet["padding"];
    // find a way to get tex width and height to avoid double loading
    loadedTextures[name] = RenderUtil::loadTexture(tilesheet["texture"], w, h);
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
            loadedSprites[fmt::format("{0}_tile_{1}", name, i)] = sprite;

            u += uStep + 2 * uPadding;
            i++;
        }
        v += vStep + 2 * vPadding;
    }
}
