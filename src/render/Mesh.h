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
    POINTERIZE(Mesh);

    Mesh();

    ~Mesh();

    unsigned int get_num_indices() override;

    std::string get_texture() override;

    void bufferVertices();
    void bufferColors();
    void bufferIndices();
private:
    _REFVAR_GET(std::vector<glm::vec3>, vertices, public);
    _REFVAR_GET(std::vector<glm::vec4>, colors, public);
    _REFVAR_GET(std::vector<unsigned int>, indices, public);

    _VAR_GETSET(GLuint, vertex_array_id, public, public){0};
    _VAR_GETSET(GLuint, vertex_buffer_id, public, public){0};
    _VAR_GETSET(GLuint, color_buffer_id, public, public){0};
    _VAR_GETSET(GLuint, element_buffer_id, public, public){0};
    _VAR_GETSET(GLenum, draw_mode, public, public){GL_TRIANGLES};
};


#endif //SOCIETY_MESH_H
