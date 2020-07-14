//
// Created by Philip on 6/3/2020.
//

#include "Mesh.h"


Mesh::Mesh() {
    glGenVertexArrays(1, &_vertex_array_id);
    glBindVertexArray(_vertex_array_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // setup verts to be first attribute with 3 components
    glGenBuffers(1, &_vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
    glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) 0            // array buffer offset
    );

    // setup vertex colors to be third attribute
    glGenBuffers(1, &_color_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer_id);
    glVertexAttribPointer(
            1,                  // attribute
            4,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) 0            // array buffer offset
    );

    // gen and bind index buffer
    glGenBuffers(1, &_element_buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _element_buffer_id);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    if (_vertex_array_id != 0)
        glDeleteVertexArrays(1, &_vertex_array_id);
    if (_vertex_buffer_id != 0)
        glDeleteBuffers(1, &_vertex_buffer_id);
    if (_color_buffer_id != 0)
        glDeleteBuffers(1, &_color_buffer_id);
    if (_element_buffer_id != 0)
        glDeleteBuffers(1, &_element_buffer_id);
}

unsigned int Mesh::get_num_indices() {
    return _indices.size();
}

std::string Mesh::get_texture() {
    return "";
}

void Mesh::bufferVertices() {
    if (_vertex_buffer_id != 0) {
        glBindVertexArray(_vertex_array_id);
        glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);
        glBindVertexArray(0);
    }
}

void Mesh::bufferColors() {
    if (_color_buffer_id != 0) {
        glBindVertexArray(_vertex_array_id);
        glBindBuffer(GL_ARRAY_BUFFER, _color_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, _colors.size()*sizeof(glm::vec4), &_colors[0], GL_STATIC_DRAW);
        glBindVertexArray(0);
    }
}

void Mesh::bufferIndices() {
    if (_element_buffer_id != 0) {
        glBindVertexArray(_vertex_array_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _element_buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
        glBindVertexArray(0);
    }
}
