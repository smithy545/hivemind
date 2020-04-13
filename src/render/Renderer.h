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
#include "Sprite.h"
#include "RenderNode.h"


class Renderer {
public:
    typedef std::shared_ptr<Renderer> Ptr;

    static const std::string CONFIG_NAME_KEY;
    static const std::string CONFIG_TILESIZE_KEY;
    static const std::string CONFIG_WIDTH_KEY;
    static const std::string CONFIG_HEIGHT_KEY;
    static const std::string CONFIG_SPRITESHEETS_KEY;
    static const std::string CONFIG_TILESHEETS_KEY;
    static const std::string CONFIG_TEXTURES_KEY;
    static const std::string CONFIG_SHADERS_KEY;
    static const std::string DEFAULT_SHADER_NAME;

    // TODO: Move these constants and tilesheet/spritesheet functionality to separate classes
    static const std::string TILESHEET_CONFIG_PADDING_KEY;
    static const std::string TILESHEET_CONFIG_TEXTURE_KEY;
    static const std::string SPRITESHEET_CONFIG_TEXTURE_KEY;


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
    void setShader(const std::string &name);
private:
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
};


#endif //SOCIETY_RENDERER_H
