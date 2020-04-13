//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_SPRITE_H
#define SOCIETY_SPRITE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


class Sprite {
public:
    typedef std::shared_ptr<Sprite> Ptr;

    std::vector<float> vertices;
    std::vector<float> uvs;
    std::vector<unsigned int> indices;

    GLuint vertexArrayId{0};
    GLuint vertexBufferId{0};
    GLuint uvBufferId{0};
    GLuint elementBufferId{0};
    std::string texture;

    Sprite();

    ~Sprite();

    void reload();
};

#endif //SOCIETY_SPRITE_H
