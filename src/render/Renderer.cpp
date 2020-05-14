//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <iostream>
#include <fmt/format.h>
#include <glm/ext.hpp>
#include <utility>

#include "util/FileUtil.h"
#include "util/MathUtil.h"
#include "util/RenderUtil.h"
#include "util/StringUtil.h"


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
        } else if (!setShader(treeHead->getShaderName())) {
            continue;
        }

        Sprite::Ptr sprite = loadedSprites[treeHead->getSpriteName()];
        GLuint texId =
                loadedTextures.find(sprite->texture) == loadedTextures.end() ? 0 : loadedTextures[sprite->texture];
        GLenum drawMode = treeHead->getMode();
        for (auto child: treeHead->getChildren()) {
            // TODO: Fix rotation about render node center
            glm::mat4 modelMatrix = glm::translate(glm::mat4(1), child.getPosition());
            modelMatrix = glm::rotate(modelMatrix, child.getAngle(), glm::vec3(0, 0, 1));
            glm::mat4 mvpMatrix = viewProj * modelMatrix;
            glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvpMatrix[0][0]);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texId);

            glBindVertexArray(sprite->vertexArrayId);
            glDrawElements(drawMode, sprite->indices.size(), GL_UNSIGNED_INT, nullptr);
        }
        treeHead = std::dynamic_pointer_cast<RenderNode>(treeHead->getNext());
    }
}

void Renderer::resize(int width, int height) {
    this->width = width;
    this->height = height;
}

bool Renderer::setShader(const std::string &name) {
    if (loadedShaders.find(name) != loadedShaders.end()) {
        currentShaderProgram = loadedShaders[name];
        glUseProgram(currentShaderProgram);
        mvpUniform = glGetUniformLocation(currentShaderProgram, "MVP");
        texUniform = glGetUniformLocation(currentShaderProgram, "tex");
        glUniform1i(texUniform, 0);
        return true;
    }
    std::cerr << "No shader found with name " << name << std::endl;
    return false;
}

void Renderer::loadShader(const std::string &name, const std::string &vertexShaderPath,
                          const std::string &fragmentShaderPath) {
    loadedShaders[name] = RenderUtil::loadShaderProgram(vertexShaderPath, fragmentShaderPath);
}

void Renderer::loadSprite(const std::string &path) {
    Sprite::Ptr sprite = std::make_shared<Sprite>();

    auto spriteData = FileUtil::readJsonFile(fmt::format("json/spritesheets/{}", path));
    float spriteWidth = spriteData[CONFIG_WIDTH_KEY];
    float spriteHeight = spriteData[CONFIG_HEIGHT_KEY];
    std::string name = spriteData[CONFIG_NAME_KEY];
    sprite->texture = spriteData[SPRITESHEET_CONFIG_TEXTURE_KEY];

    // bottom left
    sprite->vertices.emplace_back(0, 0);
    sprite->uvs.emplace_back(0, 0);

    // bottom right
    sprite->vertices.emplace_back(spriteWidth, 0);
    sprite->uvs.emplace_back(1, 0);

    // top right
    sprite->vertices.emplace_back(spriteWidth, spriteHeight);
    sprite->uvs.emplace_back(1, -1);

    // top left
    sprite->vertices.emplace_back(0, spriteHeight);
    sprite->uvs.emplace_back(0, -1);

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
            sprite->vertices.emplace_back(0, 0);
            sprite->uvs.emplace_back(u, -v);

            // bottom right
            sprite->vertices.emplace_back(contentSize, 0);
            sprite->uvs.emplace_back(u + uStep, -v);

            // top right
            sprite->vertices.emplace_back(contentSize, contentSize);
            sprite->uvs.emplace_back(u + uStep, -v - vStep);

            // top left
            sprite->vertices.emplace_back(0, contentSize);
            sprite->uvs.emplace_back(u, -v - vStep);

            // indices
            sprite->indices.push_back(0);
            sprite->indices.push_back(2);
            sprite->indices.push_back(3);

            sprite->indices.push_back(1);
            sprite->indices.push_back(2);
            sprite->indices.push_back(0);

            sprite->reload();
            loadedSprites[fmt::format("{0}_{1}", name, i)] = sprite;

            u += uStep + 2 * uPadding;
            i++;
        }
        v += vStep + 2 * vPadding;
    }
}

std::string Renderer::generateBezierSprite(const std::vector<glm::vec2> &hull, double stepSize) {

    auto curveSprite = std::make_shared<Sprite>();
    auto curve = MathUtil::generateBezierCurve(hull, stepSize);
    for (int index = 0; index < curve.size(); index++) {
        // make all points on curve red and points on hull blue
        curveSprite->vertices.push_back(curve[index]);
        curveSprite->colors.emplace_back(1, 0, 0, 1);
        curveSprite->indices.push_back(index);
    }
    curveSprite->reload();

    auto hullSprite = std::make_shared<Sprite>();
    for (int index = 0; index < hull.size(); index++) {
        hullSprite->vertices.push_back(hull[index]);
        hullSprite->colors.emplace_back(0, 0, 1, 1);
        hullSprite->indices.push_back(index);
    }
    hullSprite->reload();

    std::string id = StringUtil::uuid4();
    loadedSprites[fmt::format("curve_{}", id)] = curveSprite;
    loadedSprites[fmt::format("curve_hull_{}", id)] = hullSprite;

    return id;
}
