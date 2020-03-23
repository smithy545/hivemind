//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_RENDERER_H
#define SOCIETY_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <ui/UserInterface.h>
#include <unordered_map>
#include <vector>
#include <world/WorldMap.h>

#include "Camera.h"
#include "Sprite.h"


class Renderer {
public:
    typedef std::shared_ptr<Renderer> Ptr;

    explicit Renderer(std::string configPath);

    // lifecycle methods
    GLFWwindow *init();

    void render(GameState::Ptr state);

    void cleanup();

    // resize callback
    void resize(int width, int height);

    // state getters
    const Camera::Ptr &getCamera() const;

    int getWidth() const;

    int getHeight() const;

    int getTileSize() const;

    // state setters
    void setShader(const std::string &name);

private:
    int width{};
    int height{};
    int tileSize{};

    GLuint currentShaderProgram{};
    GLint mvpUniform;
    GLint texUniform;
    std::string configPath;
    Camera::Ptr camera;
    GLFWwindow *window;
    std::unordered_map<std::string, GLuint> loadedShaders;
    std::unordered_map<std::string, Sprite::Ptr> loadedSprites;
    std::unordered_map<std::string, GLuint> loadedTextures;

    void
    loadShader(const std::string &name, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void loadSprite(const std::string &path);

    void loadTexture(const std::string &name, const std::string &texturePath);

    void loadTileSheet(const std::string &name, const std::string &path, int sheetTileSize, int padding);
};


#endif //SOCIETY_RENDERER_H
