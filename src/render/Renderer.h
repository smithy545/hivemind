//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_RENDERER_H
#define SOCIETY_RENDERER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include "Camera.h"
#include "Sprite.h"
#include "SpriteCollection.h"


class Renderer {
public:
    typedef std::shared_ptr<Renderer> Ptr;

    explicit Renderer(const std::string &manifestFile);

    GLFWwindow *init();

    void cleanup();

    void render(const std::string &shaderName, GLint mvpUniform, GLuint texUniform);

    void resize(int width, int height);

    const Camera::Ptr &getCamera() const;

    int getWidth() const;

    int getHeight() const;

    int getTileSize() const;

    GLuint getShader(const std::string &name);

private:
    int width;
    int height;
    int tileSize{};

    Camera::Ptr camera;
    GLFWwindow *window;
    std::unordered_map<std::string, GLuint> loadedShaders;
    std::unordered_map<std::string, SpriteCollection::Ptr> loadedSprites;
    std::unordered_map<std::string, GLuint> loadedTextures;

    void
    loadShader(const std::string &name, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void loadSprite(const std::string &spritePath);

    void loadTexture(const std::string &name, const std::string &texturePath);
};


#endif //SOCIETY_RENDERER_H
