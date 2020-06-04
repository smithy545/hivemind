//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_SPRITE_H
#define SOCIETY_SPRITE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "Drawable.h"
#include "macros.h"

class Renderer;

class Sprite : public Drawable {
public:
    POINTERIZE(Sprite);

    Sprite();

    ~Sprite();

    void reload();

    const std::vector<glm::vec2> &getVertices() const;

    void setVertices(std::vector<glm::vec2> &vertices);

    const std::vector<glm::vec2> &getUvs() const;

    void setUvs(std::vector<glm::vec2> &uvs);

    const std::vector<glm::vec4> &getColors() const;

    void setColors(std::vector<glm::vec4> &colors);

    const std::vector<unsigned int> &getIndices() const;

    void setIndices(std::vector<unsigned int> &indices);

    void setTexture(const std::string &texture);

    std::string getTexture() override;

    unsigned int getNumIndices() override;

    GLuint getVertexArrayId() override;

    GLenum getDrawMode() override;
private:
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec4> colors;
    std::vector<unsigned int> indices;

    GLuint vertexArrayId{0};
    GLuint vertexBufferId{0};
    GLuint uvBufferId{0};
    GLuint colorBufferId{0};
    GLuint elementBufferId{0};
    std::string texture{""};
};

#endif //SOCIETY_SPRITE_H
