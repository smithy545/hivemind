//
// Created by Philip on 6/3/2020.
//

#include "Mesh.h"


Mesh::Mesh() {
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);

    // setup verts to be first attribute with 3 components
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) 0            // array buffer offset
    );

    // setup vertex colors to be third attribute
    glGenBuffers(1, &colorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
    glVertexAttribPointer(
            2,                  // attribute
            4,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) 0            // array buffer offset
    );

    // gen and bind index buffer
    glGenBuffers(1, &elementBufferId);
}

Mesh::~Mesh() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    if (vertexArrayId != 0)
        glDeleteVertexArrays(1, &vertexArrayId);
    if (vertexBufferId != 0)
        glDeleteBuffers(1, &vertexBufferId);
    if (colorBufferId != 0)
        glDeleteBuffers(1, &colorBufferId);
    if (elementBufferId != 0)
        glDeleteBuffers(1, &elementBufferId);
}

const std::vector<glm::vec3> &Mesh::getVertices() const {
    return vertices;
}

void Mesh::setVertices(std::vector<glm::vec3> &vertices) {
    Mesh::vertices = vertices;
    if (vertexBufferId != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    }
}

const std::vector<glm::vec4> &Mesh::getColors() const {
    return colors;
}

void Mesh::setColors(std::vector<glm::vec4> &colors) {
    Mesh::colors = colors;
    if (colorBufferId != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
        glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);
    }
}

const std::vector<unsigned int> &Mesh::getIndices() const {
    return indices;
}

void Mesh::setIndices(std::vector<unsigned int> &indices) {
    Mesh::indices = indices;
    if (elementBufferId != 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    }
}

std::string Mesh::getTexture() {
    return "";
}

GLuint Mesh::getVertexArrayId() {
    return vertexArrayId;
}

unsigned int Mesh::getNumIndices() {
    return indices.size();
}

GLenum Mesh::getDrawMode() {
    return mode;
}

void Mesh::setDrawMode(GLenum drawMode) {
    mode = drawMode;
}