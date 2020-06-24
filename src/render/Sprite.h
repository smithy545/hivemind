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

    _REFVAR_GET(vertices, std::vector<glm::vec2>, public)
    _REFVAR_GET(uvs, std::vector<glm::vec2>, public)
    _REFVAR_GET(colors, std::vector<glm::vec4>, public)
    _REFVAR_GET(indices, std::vector<unsigned int>, public)

    _VAR_GETSET_INIT(vertex_array_id, GLuint, public, public, 0)
    _VAR_GETSET_INIT(vertex_buffer_id, GLuint, public, public, 0)
    _VAR_GETSET_INIT(uv_buffer_id, GLuint, public, public, 0)
    _VAR_GETSET_INIT(color_buffer_id, GLuint, public, public, 0)
    _VAR_GETSET_INIT(element_buffer_id, GLuint, public, public, 0)
    _VAR_GETSET(texture, std::string, public, public)
};

#endif //SOCIETY_SPRITE_H
