//
// Created by Philip on 3/1/2020.
//

#ifndef HIVEMIND_MESH_H
#define HIVEMIND_MESH_H

#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Mesh {
public:
    typedef std::shared_ptr<Mesh> Ptr;

    std::vector<float> vertices;
    std::vector<float> uvs;
    std::vector<unsigned int> indices;

    GLuint vertexArrayId{0};
    GLuint vertexBufferId{0};
    GLuint uvBufferId{0};
    GLuint elementBufferId{0};
    GLuint textureId{0};

    Mesh() {
        glGenVertexArrays(1, &vertexArrayId);
        glBindVertexArray(vertexArrayId);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // setup empty texture for later
        glGenTextures(1, &textureId);

        // setup verts to be first attribute with 3 components
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

    ~Mesh() {
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
    }

    void reload() {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), &uvs[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
    }
};

#endif //HIVEMIND_MESH_H
