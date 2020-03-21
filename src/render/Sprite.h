//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_SPRITE_H
#define SOCIETY_SPRITE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Sprite {
public:
    typedef std::shared_ptr<Sprite> Ptr;

    class Animation {
    public:
        int offset;
        int length;

        Animation() : Animation(0, 1) {}

        Animation(int offset, int length) : offset(offset), length(length) {}
    };

    std::vector<float> vertices;
    std::vector<float> uvs;
    std::vector<unsigned int> indices;

    GLuint vertexArrayId{0};
    GLuint vertexBufferId{0};
    GLuint uvBufferId{0};
    GLuint elementBufferId{0};
    std::string texture;
    std::unordered_map<std::string, Animation> animations;

    Sprite();

    ~Sprite();

    void reload();

    void addAnimation(const std::string &name, int uvOffset, int length);

    bool setAnimation(const std::string &name, int frame);
};

#endif //SOCIETY_SPRITE_H
