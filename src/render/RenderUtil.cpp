//
// Created by Philip on 3/1/2020.
//

#include "RenderUtil.h"

#include <fstream>
#include <iostream>


void RenderUtil::renderMesh(const std::weak_ptr<Mesh> &meshPtr) {
    Mesh::Ptr mesh = meshPtr.lock();

    glBindVertexArray(mesh->vertexArrayId);
    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, nullptr);
}


char *RenderUtil::readShader(const std::string &path) {
    std::ifstream shaderStream("../res/shaders/" + path, std::ifstream::ate);
    if (shaderStream) {
        // get file length (ifstream::ate flag puts cursor at end of file)
        int shaderLength = shaderStream.tellg();
        shaderStream.seekg(0, std::ios_base::beg);

        // store in buffer
        char *shaderBuffer = new char[shaderLength];
        int count = 0;
        while (shaderStream.read(shaderBuffer + count, shaderLength - count) || shaderStream.gcount() != 0) {
            count += shaderStream.gcount();
        }
        shaderStream.close();

        // null terminate because C++ fucking sucks
        shaderBuffer[count] = '\0';

        return shaderBuffer;
    }

    // open failed for some reason
    std::cout << "Error opening shader at res/shaders/" << path << std::endl;
    return nullptr;
}
