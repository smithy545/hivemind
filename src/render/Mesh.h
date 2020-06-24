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
    _REFVAR_GET(vertices, std::vector<glm::vec3>, public)
    _REFVAR_GET(colors, std::vector<glm::vec4>, public)
    _REFVAR_GET(indices, std::vector<unsigned int>, public)

    _VAR_GETSET_INIT(vertex_array_id, GLuint, public, public, 0)
    _VAR_GETSET_INIT(vertex_buffer_id, GLuint, public, public, 0)
    _VAR_GETSET_INIT(color_buffer_id, GLuint, public, public, 0)
    _VAR_GETSET_INIT(element_buffer_id, GLuint, public, public, 0)
    _VAR_GETSET_INIT(draw_mode, GLenum, public, public, GL_TRIANGLES)
};


#endif //SOCIETY_MESH_H
