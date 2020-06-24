//
// Created by smith on 3/16/2020.
//

#include "Sprite.h"

#include <utility>


Sprite::Sprite(std::string texture) : _texture(std::move(texture)) {
    glGenVertexArrays(1, &_vertex_array_id);
    glBindVertexArray(_vertex_array_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // setup verts to be first attribute with 3 components
    glGenBuffers(1, &_vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
    glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) 0            // array buffer offset
    );

    // setup vertex uvs to be second attribute
    glGenBuffers(1, &_uv_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _uv_buffer_id);
    glVertexAttribPointer(
            1,                  // attribute
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) 0            // array buffer offset
    );

    // setup vertex colors to be third attribute
    glGenBuffers(1, &_color_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer_id);
    glVertexAttribPointer(
            2,                  // attribute
            4,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) 0            // array buffer offset
    );

    // gen and bind index buffer
    glGenBuffers(1, &_element_buffer_id);
}

Sprite::~Sprite() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    if (_vertex_array_id != 0)
        glDeleteVertexArrays(1, &_vertex_array_id);
    if (_vertex_buffer_id != 0)
        glDeleteBuffers(1, &_vertex_buffer_id);
    if (_uv_buffer_id != 0)
        glDeleteBuffers(1, &_uv_buffer_id);
    if (_color_buffer_id != 0)
        glDeleteBuffers(1, &_color_buffer_id);
    if (_element_buffer_id != 0)
        glDeleteBuffers(1, &_element_buffer_id);
}

unsigned int Sprite::get_num_indices() {
    return _indices.size();
}

GLenum Sprite::get_draw_mode() {
    return GL_TRIANGLES;
}