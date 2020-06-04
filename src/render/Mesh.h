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

    const std::vector<glm::vec3> &getVertices() const;

    void setVertices(std::vector<glm::vec3> &vertices);

    const std::vector<glm::vec4> &getColors() const;

    void setColors(std::vector<glm::vec4> &colors);

    const std::vector<unsigned int> &getIndices() const;

    void setIndices(std::vector<unsigned int> &indices);

    void setDrawMode(GLenum drawMode);

    std::string getTexture() override;

    unsigned int getNumIndices() override;

    GLuint getVertexArrayId() override;

    GLenum getDrawMode() override;
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec4> colors;
    std::vector<unsigned int> indices;

    GLuint vertexArrayId{0};
    GLuint vertexBufferId{0};
    GLuint colorBufferId{0};
    GLuint elementBufferId{0};
    GLenum mode{GL_TRIANGLES};
};


#endif //SOCIETY_MESH_H
