//
// Created by smith on 3/16/2020.
//

#include "Sprite.h"


Sprite::Sprite() {
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // setup verts to be first attribute with 2 components
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) 0            // array buffer offset
    );

    // setup vertex uvs to be second attribute
    glGenBuffers(1, &uvBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glVertexAttribPointer(
            1,                  // attribute
            2,                  // size
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
}

Sprite::~Sprite() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    if (vertexArrayId != 0)
        glDeleteVertexArrays(1, &vertexArrayId);
    if (vertexBufferId != 0)
        glDeleteBuffers(1, &vertexBufferId);
    if (uvBufferId != 0)
        glDeleteBuffers(1, &uvBufferId);
    if (colorBufferId != 0)
        glDeleteBuffers(1, &colorBufferId);
    if (elementBufferId != 0)
        glDeleteBuffers(1, &elementBufferId);
};

void Sprite::reload() {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

    // pad to prevent memory access error by shaders
    while (uvs.size() < vertices.size())
        uvs.emplace_back();
    while (colors.size() < vertices.size())
        colors.emplace_back();

    // use vertices.size() so no unused uvs/colors are loaded unnecessarily
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}
