//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <iostream>
#include <fmt/format.h>
#include <glm/ext.hpp>
#include <utility>
#include <util/FileUtil.h>
#include <util/RenderUtil.h>

const std::string Renderer::CONFIG_NAME_KEY = "name";
const std::string Renderer::CONFIG_WIDTH_KEY = "width";
const std::string Renderer::CONFIG_HEIGHT_KEY = "height";
const std::string Renderer::CONFIG_SPRITESHEETS_KEY = "spritesheets";
const std::string Renderer::CONFIG_TILESHEETS_KEY = "tilesheets";
const std::string Renderer::CONFIG_TILESIZE_KEY = "tileSize";
const std::string Renderer::CONFIG_TEXTURES_KEY = "textures";
const std::string Renderer::CONFIG_SHADERS_KEY = "shaders";
const std::string Renderer::DEFAULT_SHADER_NAME = "default";
const std::string Renderer::TILESHEET_CONFIG_PADDING_KEY = "padding";
const std::string Renderer::TILESHEET_CONFIG_TEXTURE_KEY = "texture";
const std::string Renderer::SPRITESHEET_CONFIG_TEXTURE_KEY = "textureName";

Renderer::Renderer(std::string configPath) : configPath(std::move(configPath)), window(nullptr) {}

int Renderer::getWidth() const {
    return width;
}

int Renderer::getHeight() const {
    return height;
}

GLFWwindow *Renderer::init() {
    // read config
    auto config = FileUtil::readJsonFile(configPath);
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
    window = glfwCreateWindow(width, height, "SOCIETY", nullptr, nullptr);
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

    setShader(DEFAULT_SHADER_NAME);

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

void Renderer::render(RenderNode::Ptr treeHead, const Camera::Ptr &camera) {
    glUseProgram(currentShaderProgram);
    glm::mat4 viewProj = camera->getViewProjectionMatrix();

    while (treeHead != nullptr) {
        std::string spriteName = treeHead->getSpriteName();
        if (loadedSprites.find(spriteName) == loadedSprites.end()) {
            std::cerr << "Can't find sprite " << treeHead->getSpriteName() << std::endl;
            continue;
        } else if (loadedTextures.find(loadedSprites[spriteName]->texture) == loadedTextures.end()) {
            std::cerr << "Can't find texture " << loadedSprites[spriteName]->texture << " for sprite " << spriteName
                      << std::endl;
            continue;
        }
        Sprite::Ptr sprite = loadedSprites[treeHead->getSpriteName()];
        GLuint texId = loadedTextures[sprite->texture];
        for (auto child: treeHead->getChildren()) {
            glm::mat4 modelMatrix = glm::translate(glm::mat4(1), child.getPosition());
            modelMatrix = glm::rotate(modelMatrix, child.getAngle(), glm::vec3(0, 0, 1));
            glm::mat4 mvpMatrix = viewProj * modelMatrix;
            glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvpMatrix[0][0]);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texId);

            glBindVertexArray(sprite->vertexArrayId);
            glDrawElements(GL_TRIANGLES, sprite->indices.size(), GL_UNSIGNED_INT, nullptr);
        }
        treeHead = treeHead->getNext();
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
    Sprite::Ptr sprite = std::make_shared<Sprite>();

    auto spriteData = FileUtil::readJsonFile(fmt::format("json/spritesheets/{}", path));
    float width = spriteData[CONFIG_WIDTH_KEY];
    float height = spriteData[CONFIG_HEIGHT_KEY];
    std::string name = spriteData[CONFIG_NAME_KEY];
    sprite->texture = spriteData[SPRITESHEET_CONFIG_TEXTURE_KEY];

    // bottom left
    sprite->vertices.push_back(0);
    sprite->vertices.push_back(0);

    sprite->uvs.push_back(0);
    sprite->uvs.push_back(0);

    // bottom right
    sprite->vertices.push_back(width);
    sprite->vertices.push_back(0);

    sprite->uvs.push_back(1);
    sprite->uvs.push_back(0);

    // top right
    sprite->vertices.push_back(width);
    sprite->vertices.push_back(height);

    sprite->uvs.push_back(1);
    sprite->uvs.push_back(-1);

    // top left
    sprite->vertices.push_back(0);
    sprite->vertices.push_back(height);

    sprite->uvs.push_back(0);
    sprite->uvs.push_back(-1);

    // indices
    sprite->indices.push_back(0);
    sprite->indices.push_back(2);
    sprite->indices.push_back(3);

    sprite->indices.push_back(1);
    sprite->indices.push_back(2);
    sprite->indices.push_back(0);

    sprite->reload();

    loadedSprites[name] = sprite;
}

void Renderer::loadTexture(const std::string &name, const std::string &texturePath) {
    int w, h;
    loadedTextures[name] = RenderUtil::loadTexture(texturePath, w, h);
}

void Renderer::loadTileSheet(const std::string &path) {
    auto tilesheet = FileUtil::readJsonFile(fmt::format("json/tilesheets/{}", path));

    std::string name = tilesheet[CONFIG_NAME_KEY];
    int sheetTileSize = tilesheet[CONFIG_TILESIZE_KEY];
    int padding = tilesheet[TILESHEET_CONFIG_PADDING_KEY];

    int w, h;
    loadedTextures[name] = RenderUtil::loadTexture(tilesheet[TILESHEET_CONFIG_TEXTURE_KEY], w, h);

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
