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

    Renderer(int width, int height);

    GLFWwindow *init();

    void cleanup();

    void resize(int width, int height);

    void renderSprites(const std::string &shaderName, GLint mvpUniform, GLint texUniform);

    void storeSprite(const std::string &name, const Sprite::Ptr &sprite);

    const Camera::Ptr &getCamera() const;

    int getWidth() const;

    int getHeight() const;

    int getTileSize() const;

    GLuint getShader(const std::string &name);

    SpriteCollection::Ptr getSprite(const std::string &name);
private:
    int width;
    int height;
    int tileSize{};

    Camera::Ptr camera;
    GLFWwindow *window;
    std::unordered_map<std::string, SpriteCollection::Ptr> loadedSprites;
    std::unordered_map<std::string, GLuint> loadedShaders;
};


#endif //SOCIETY_RENDERER_H
