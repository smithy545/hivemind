//
// Created by Philip on 2/10/2020.
//

#ifndef HIVEMIND_MESH_H
#define HIVEMIND_MESH_H

#include <memory>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>


class Mesh {
public:
    typedef std::shared_ptr<Mesh> Ptr;

    Mesh(int numVertices, int numIndices) : numVertices(numVertices), numIndices(numIndices) {
        glGenVertexArrays(1, &vertexArrayId);
        glBindVertexArray(vertexArrayId);
        glGenBuffers(1, &vertexBufferId);
        glGenBuffers(1, &elementBufferId);
    }

    ~Mesh() {
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        if (vertexArrayId != 0)
            glDeleteVertexArrays(1, &vertexArrayId);
        if (vertexBufferId != 0)
            glDeleteBuffers(1, &vertexBufferId);
        if (elementBufferId != 0)
            glDeleteBuffers(1, &elementBufferId);
    }

    GLuint vertexArrayId;
    GLuint vertexBufferId;
    GLuint elementBufferId;
    int numVertices;
    int numIndices;
};


#endif //HIVEMIND_MESH_H
