//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <iostream>
#include <fmt/format.h>
#include <glm/ext.hpp>

#include "util/FileUtil.h"
#include "util/MathUtil.h"
#include "util/RenderUtil.h"
#include "util/StringUtil.h"


Renderer::Renderer() : window(nullptr) {}

int Renderer::getWidth() const {
    return width;
}

int Renderer::getHeight() const {
    return height;
}

GLFWwindow *Renderer::init(const std::string& configPath) {
    auto config = FileUtil::readJsonFile(configPath, CONFIG_SCHEMA);
    width = config[WIDTH_KEY];
    height = config[HEIGHT_KEY];

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

    // enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // shaders
    for (const auto &shader: config[SHADERS_KEY].items()) {
        std::cout << fmt::format("Loading shader \"{0}\" from {1} {2} ", shader.key(), shader.value()[0],
                                 shader.value()[1])
                  << std::endl;
        loadShader(shader.key(), shader.value()[0], shader.value()[1]);
    }

    // image textures
    for (const auto &tex: config[TEXTURES_KEY].items()) {
        std::cout << fmt::format("Loading texture \"{0}\" from {1}", tex.key(), tex.value()) << std::endl;
        loadTexture(tex.key(), tex.value());
    }

    // tilesheet textures
    for (const auto &tilesheet: config[TILESHEETS_KEY]) {
        std::cout << fmt::format("Loading tilesheet from {0}", tilesheet) << std::endl;
        loadTileSheet(tilesheet);
    }

    // sprites
    for (const auto &sprite: config[SPRITESHEETS_KEY]) {
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

void Renderer::render(const RenderNode::Ptr &treeHead, const Camera &camera) {
    glUseProgram(currentShaderProgram);
    auto viewProj = camera.getViewProjectionMatrix();
    auto node = treeHead;
    while (node != nullptr) {
        if(setShader(node->getShaderName()) && node->getEntity() != nullptr) {
            glBindVertexArray(node->getEntity()->getVertexArrayId());
            auto tex = node->getEntity()->getTexture();
            if (!tex.empty() && loadedTextures.find(tex) != loadedTextures.end()) {
                GLuint texId = loadedTextures[tex];
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texId);
            }

            for (const auto &body: node->getBodies()) {
                // translate to world position
                glm::mat4 modelMatrix = glm::translate(glm::mat4(1), body->getOrigin());
                glm::mat4 mvpMatrix = viewProj * modelMatrix;
                glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvpMatrix[0][0]);
                glDrawElements(node->getEntity()->getDrawMode(), node->getEntity()->getNumIndices() * sizeof(unsigned int),
                               GL_UNSIGNED_INT, nullptr);
            }
        }
        node = std::dynamic_pointer_cast<RenderNode>(node->getNext());
    }
}

void Renderer::resize(int width, int height) {
    this->width = width;
    this->height = height;
}

bool Renderer::setShader(const std::string &name) {
    if(name == currentShader)
        return true;
    else if (loadedShaders.find(name) != loadedShaders.end()) {
        currentShader = name;
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
    auto spriteData = FileUtil::readJsonFile(fmt::format("spritesheets/{}", path), SPRITE_SCHEMA);
    float spriteWidth = spriteData[WIDTH_KEY];
    float spriteHeight = spriteData[HEIGHT_KEY];
    std::string name = spriteData[NAME_KEY];
    sprite->setTexture(spriteData[TEXTURE_KEY]);

    std::vector<glm::vec2> vertices, uvs;
    std::vector<unsigned int> indices;
    // bottom left
    vertices.emplace_back(0, 0);
    uvs.emplace_back(0, 0);

    // bottom right
    vertices.emplace_back(spriteWidth, 0);
    uvs.emplace_back(1, 0);

    // top right
    vertices.emplace_back(spriteWidth, spriteHeight);
    uvs.emplace_back(1, -1);

    // top left
    vertices.emplace_back(0, spriteHeight);

    uvs.emplace_back(0, -1);

    // indices
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);

    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(0);

    sprite->setVertices(vertices);
    sprite->setUvs(uvs);
    sprite->setIndices(indices);

    loadedSprites[name] = sprite;
}

void Renderer::loadTexture(const std::string &name, const std::string &texturePath) {
    int w, h;
    loadedTextures[name] = RenderUtil::loadTexture(texturePath, w, h);
}

void Renderer::loadTileSheet(const std::string &path) {
    auto tilesheet = FileUtil::readJsonFile(fmt::format("tilesheets/{}", path), TILESHEET_SCHEMA);

    std::string name = tilesheet[NAME_KEY];
    int sheetTileSize = tilesheet[TILESIZE_KEY];
    int w, h;
    loadedTextures[name] = RenderUtil::loadTexture(tilesheet[TEXTURE_KEY], w, h);
    loadedTextures[name] = RenderUtil::loadTexture(tilesheet[TEXTURE_KEY], w, h);

    int i = 0;
    float uStep = sheetTileSize / (1.0 * w);
    float vStep = sheetTileSize / (1.0 * h);
    for (float v = 0; v >= -1.0; v -= vStep) {
        for (float u = 0; u < 1.0; u += uStep) {
            Sprite::Ptr sprite = std::make_shared<Sprite>();
            sprite->setTexture(name);

            std::vector<glm::vec2> vertices, uvs;
            std::vector<unsigned int> indices;
            // bottom left
            vertices.emplace_back(0, 0);
            uvs.emplace_back(u, v);

            // bottom right
            vertices.emplace_back(sheetTileSize, 0);
            uvs.emplace_back(u + uStep, v);

            // top right
            vertices.emplace_back(sheetTileSize, sheetTileSize);
            uvs.emplace_back(u + uStep, v - vStep);

            // top left
            vertices.emplace_back(0, sheetTileSize);
            uvs.emplace_back(u, v - vStep);

            // indices
            indices.push_back(0);
            indices.push_back(2);
            indices.push_back(3);

            indices.push_back(1);
            indices.push_back(2);
            indices.push_back(0);

            sprite->setVertices(vertices);
            sprite->setUvs(uvs);
            sprite->setIndices(indices);

            loadedSprites[fmt::format("{0}_{1}", name, i)] = sprite;
            i++;
        }
    }

    // setup sprites
    json_validator validator;
    try {
        validator.set_root_schema(SPRITE_SCHEMA);
    } catch (std::exception &e) {
        std::cerr << "Schema error: " << e.what() << std::endl;
        return;
    }
    for (const auto& spriteInfo: tilesheet[SPRITES_KEY]) {
        try {
            validator.validate(spriteInfo);
        } catch(std::exception &e) {
            std::cerr << "Validation error: " << e.what() << std::endl;
            continue;
        }

        if(loadedSprites.find(spriteInfo[TEXTURE_KEY]) != loadedSprites.end()) {
            // replace tile name with sprite name
            loadedSprites[spriteInfo[NAME_KEY]] = loadedSprites[spriteInfo[TEXTURE_KEY]];
            loadedSprites.erase(spriteInfo[TEXTURE_KEY]);
        }
    }
}

Mesh::Ptr Renderer::generateBezierMesh(const std::vector<glm::vec3> &hull, double stepSize, glm::vec4 color) {
    auto curve = MathUtil::generateBezierCurve(hull, stepSize);
    std::vector<glm::vec3> verts;
    std::vector<glm::vec4> colors;
    std::vector<unsigned int> indices;
    for (int index = 0; index < curve.size(); index++) {
        // make all points on curve red
        verts.emplace_back(curve[index].x, -curve[index].y, curve[index].z);
        colors.push_back(color);
        indices.push_back(index);
    }

    auto mesh = std::make_shared<Mesh>();
    mesh->setVertices(verts);
    mesh->setColors(colors);
    mesh->setIndices(indices);
    mesh->setDrawMode(GL_LINE_STRIP);

    return mesh;
}

Mesh::Ptr Renderer::generateLineMesh(const std::vector<glm::vec3> &points, glm::vec4 color) {
    std::vector<glm::vec3> verts;
    std::vector<glm::vec4> colors;
    std::vector<unsigned int> indices;
    for (int index = 0; index < points.size(); index++) {
        // make all points on line red
        verts.emplace_back(points[index].x, -points[index].y, points[index].z);
        colors.push_back(color);
        indices.push_back(index);
    }

    auto mesh = std::make_shared<Mesh>();
    mesh->setVertices(verts);
    mesh->setColors(colors);
    mesh->setIndices(indices);
    mesh->setDrawMode(GL_LINE_STRIP);

    return mesh;
}

Mesh::Ptr Renderer::generateBoxMeshTriangles(int width, int height, int length, glm::vec4 color) {
    auto verts = MathUtil::generateBox(width, height, length);
    // indices for triangles on box surface
    std::vector<unsigned int> indices = {
            1, 0, 2,
            2, 0, 3,

            4, 5, 6,
            6, 7, 4,

            0, 4, 7,
            7, 3, 0,

            6, 5, 1,
            2, 6, 1,

            4, 0, 5,
            5, 0, 1,

            6, 2, 7,
            7, 2, 3,
    };
    // set colors for every vert
    std::vector<glm::vec4> colors;
    colors.reserve(verts.size());
    for (int i = 0; i < verts.size(); i++) {
        colors.push_back(color);
    }

    auto mesh = std::make_shared<Mesh>();
    mesh->setVertices(verts);
    mesh->setColors(colors);
    mesh->setIndices(indices);
    mesh->setDrawMode(GL_TRIANGLES);

    return mesh;
}

Mesh::Ptr Renderer::generateBoxMeshLines(int width, int height, int length, glm::vec4 color) {
    auto verts = MathUtil::generateBox(width, height, length);
    // indices for triangles on box surface
    std::vector<unsigned int> indices = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,

        4, 5,
        5, 6,
        6, 7,
        7, 4,

        0, 4,
        1, 5,
        2, 6,
        3, 7
    };
    // set colors for every vert
    std::vector<glm::vec4> colors;
    colors.reserve(verts.size());
    for (int i = 0; i < verts.size(); i++) {
        colors.push_back(color);
    }

    auto mesh = std::make_shared<Mesh>();
    mesh->setVertices(verts);
    mesh->setColors(colors);
    mesh->setIndices(indices);
    mesh->setDrawMode(GL_LINES);

    return mesh;
}
