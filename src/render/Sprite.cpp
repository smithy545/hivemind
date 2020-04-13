//
// Created by smith on 3/16/2020.
//

#include "Sprite.h"

#include <iostream>


Sprite::Sprite() {
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

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

    // setup uvs to be second attribute
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
    if (elementBufferId != 0)
        glDeleteBuffers(1, &elementBufferId);
};

void Sprite::reload() {
    // 4 verts x 2 components = 8
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), &uvs[0], GL_STATIC_DRAW);

    // 2 triangles x 3 indices = 6
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), &indices[0], GL_STATIC_DRAW);
}
