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

    explicit Sprite(std::string texture);

    ~Sprite();

    unsigned int get_num_indices() override;

    GLenum get_draw_mode() override;

    _REFVAR_GET(std::vector<glm::vec2>, vertices, public);
    _REFVAR_GET(std::vector<glm::vec2>, uvs, public);
    _REFVAR_GET(std::vector<glm::vec4>, colors, public);
    _REFVAR_GET(std::vector<unsigned int>, indices, public);

    _VAR_GETSET(GLuint, vertex_array_id, public, public){0};
    _VAR_GETSET(GLuint, vertex_buffer_id, public, public){0};
    _VAR_GETSET(GLuint, uv_buffer_id, public, public){0};
    _VAR_GETSET(GLuint, color_buffer_id, public, public){0};
    _VAR_GETSET(GLuint, element_buffer_id, public, public){0};
    _VAR_GETSET(std::string, texture, public, public);
};

#endif //SOCIETY_SPRITE_H
