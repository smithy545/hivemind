//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_RENDERER_H
#define SOCIETY_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Camera.h"
#include "RenderNode.h"
#include "Sprite.h"


class Renderer {
public:
    typedef std::shared_ptr<Renderer> Ptr;

    explicit Renderer(std::string configPath);

    // lifecycle methods
    GLFWwindow *init();

    void render(RenderNode::Ptr treeHead, const Camera::Ptr &camera);

    void cleanup();

    // resize callback
    void resize(int width, int height);

    // state getters
    int getWidth() const;

    int getHeight() const;

    // state setters
    bool setShader(const std::string &name);

private:
    const std::string NAME_KEY{"name"};
    const std::string WIDTH_KEY{"width"};
    const std::string HEIGHT_KEY{"height"};
    const std::string SPRITESHEETS_KEY{"spritesheets"};
    const std::string TILESHEETS_KEY{"tilesheets"};
    const std::string TILESIZE_KEY{"tilesize"};
    const std::string TILENAMES_KEY{"tilenames"};
    const std::string TEXTURE_KEY{"texture"};
    const std::string TEXTURES_KEY{"textures"};
    const std::string TEXTURE_NAME_KEY{"textureName"};
    const std::string SHADERS_KEY{"shaders"};
    const std::string DEFAULT_SHADER_NAME{"texture"};

    int width{};
    int height{};
    GLuint currentShaderProgram{};
    GLint mvpUniform{};
    GLint texUniform{};
    std::string configPath;
    GLFWwindow *window;
    std::unordered_map<std::string, GLuint> loadedShaders;
    std::unordered_map<std::string, Sprite::Ptr> loadedSprites;
    std::unordered_map<std::string, GLuint> loadedTextures;

    void
    loadShader(const std::string &name, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void loadSprite(const std::string &path);

    void loadTexture(const std::string &name, const std::string &texturePath);

    void loadTileSheet(const std::string &path);

    std::string generateBezierSprite(const std::vector<glm::vec2> &hull, double stepSize);
};

#endif //SOCIETY_RENDERER_H
