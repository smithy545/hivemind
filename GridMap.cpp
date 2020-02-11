//
// Created by philip on 1/23/20.
//

#include "GridMap.h"


GridMap::GridMap(int width, int height) : width(width), height(height), nodes(width * height), mesh(nullptr) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            nodes[y * width + x] = std::make_shared<MapNode>(x, y);
            MapNode::Ptr node = nodes[y * width + x];
            const bool xgt0 = x > 0;
            const bool ygt0 = y > 0;
            const bool xltw = x < width - 1;
            const bool ylth = y < height - 1;
            if (xgt0)
                node->neighbors.push_back(nodes[y * width + x - 1]);
            if(xltw)
                node->neighbors.push_back(nodes[y*width + x + 1]);
            if(ygt0)
                node->neighbors.push_back(nodes[(y - 1)*width + x]);
            if(ylth)
                node->neighbors.push_back(nodes[(y + 1)*width + x]);
            if(xgt0 && ygt0)
                node->neighbors.push_back(nodes[(y - 1)*width + x - 1]);
            if(xltw && ylth)
                node->neighbors.push_back(nodes[(y + 1)*width + x + 1]);
            if(xgt0 && ylth)
                node->neighbors.push_back(nodes[(y + 1)*width + x - 1]);
            if(xltw && ygt0)
                node->neighbors.push_back(nodes[(y - 1)*width + x + 1]);
        }
    }
}

MapNode::Ptr GridMap::getNode(int x, int y) {
    unsigned int index = y * width + x;
    if(index < 0 || index > nodes.size())
        return nullptr;
    return nodes[index];
}

Mesh::Ptr GridMap::generateMesh(float screenWidth, float screenHeight, float tilesize) {
    if (mesh == nullptr) {
        int N = nodes.size();
        mesh = std::make_shared<Mesh>(8 * N, 6 * N);

        float *vertices = new float[mesh->numVertices];
        unsigned int *indices = new unsigned int[mesh->numIndices];
        int i = 0;
        int j = 0;
        for (const auto &node: nodes) {
            float x = node->x * tilesize - screenWidth;
            float y = node->y * tilesize - screenHeight;

            // top right
            vertices[i] = (x - tilesize) / screenWidth;
            vertices[i + 1] = y / screenHeight;
            // bottom right
            vertices[i + 2] = (x - tilesize) / screenWidth;
            vertices[i + 3] = (y - tilesize) / screenHeight;
            // bottom left
            vertices[i + 4] = x / screenWidth;
            vertices[i + 5] = (y - tilesize) / screenHeight;
            // top left
            vertices[i + 6] = x / screenWidth;
            vertices[i + 7] = y / screenHeight;

            indices[j] = i / 2;
            indices[j + 1] = i / 2 + 1;
            indices[j + 2] = i / 2 + 3;
            indices[j + 3] = i / 2 + 1;
            indices[j + 4] = i / 2 + 2;
            indices[j + 5] = i / 2 + 3;

            i += 8;
            j += 6;
        }

        glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, mesh->numVertices * sizeof(float), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        delete[] vertices;
        delete[] indices;
    }
    return mesh;
}