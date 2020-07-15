//
// Created by Philip on 6/3/2020.
//

#ifndef SOCIETY_MESH_H
#define SOCIETY_MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Drawable.h"
#include "macros.h"


class Mesh : public Drawable {
public:
    PTR(Mesh);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec4> colors;
    std::vector<unsigned int> indices;

    Mesh();

    ~Mesh();

    unsigned int get_num_indices() const override;

    std::string get_texture() const override;

    void bufferVertices();
    void bufferColors();
    void bufferIndices();
    void buffer();
private:
    VAR(GLenum, draw_mode, public, public){GL_TRIANGLES};
    VAR(GLuint, vertex_array_id, public, public){0};
    VAR(GLuint, vertex_buffer_id, public, public){0};
    VAR(GLuint, color_buffer_id, public, public){0};
    VAR(GLuint, element_buffer_id, public, public){0};
};


#endif //SOCIETY_MESH_H
