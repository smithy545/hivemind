//
// Created by Philip on 3/1/2020.
//

#include "MeshUtil.h"

#include <iostream>

/*
Mesh::Ptr MeshUtil::generateTerrainMesh(float screenWidth, float screenHeight, float tileSize) {
Mesh::Ptr mesh;
float *vertices{nullptr};
unsigned int *indices{nullptr};

int N = screenHeight * screenWidth / (tileSize * tileSize) + 1;
std::cout << "Allocating " << 8 * N << " vertices and " << 6 * N << " indices for map mesh" << std::endl;

// set size to max possible visible
vertices = new float[8 * N];
indices = new unsigned int[6 * N];
mesh = std::make_shared<Mesh>(8 * N, 6 * N);

glBindVertexArray(mesh->getVertexArrayId());
glEnableVertexAttribArray(0);

// load vertex data into buffer
glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBufferId());
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

// load index data into buffer
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getElementBufferId());


float x = entity->getPosition()->getX() * tileSize;
float y = entity->getPosition()->getY() * tileSize;

// top right
vertices[i] = x;
vertices[i + 1] = (y + tileSize);
// bottom right
vertices[i + 2] = x;
vertices[i + 3] = y;
// bottom left
vertices[i + 4] = (x + tileSize);
vertices[i + 5] = y;
// top left
vertices[i + 6] = (x + tileSize);
vertices[i + 7] = (y + tileSize);

// two triangles that make a square at the given tile location
indices[j] = i / 2;
indices[j + 1] = i / 2 + 1;
indices[j + 2] = i / 2 + 3;
indices[j + 3] = i / 2 + 1;
indices[j + 4] = i / 2 + 2;
indices[j + 5] = i / 2 + 3;

i += 8;
j += 6;



// TODO: selectively call glBufferSubdata on vertices that change, i.e. individual actor meshes

// load vertex data into buffer
glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBufferId());
glBufferData(GL_ARRAY_BUFFER, mesh->getNumVertices() * sizeof(float), vertices, GL_STATIC_DRAW);

// load index data into buffer
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getElementBufferId());
glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getNumIndices() * sizeof(unsigned int), indices, GL_STATIC_DRAW);

return mesh;
}


Mesh::Ptr MeshUtil::generateCubeMesh(double width, double height, double length) {

Mesh::Ptr mesh = std::make_shared<Mesh>();

mesh->vertices.push_back(-0.5 * width);
mesh->vertices.push_back(-0.5 * height);
mesh->vertices.push_back(-0.5 * length);

mesh->vertices.push_back(-0.5 * width);
mesh->vertices.push_back(0.5 * height);
mesh->vertices.push_back(-0.5 * length);

mesh->vertices.push_back(-0.5 * width);
mesh->vertices.push_back(-0.5 * height);
mesh->vertices.push_back(0.5 * length);

mesh->vertices.push_back(0.5 * width);
mesh->vertices.push_back(-0.5 * height);
mesh->vertices.push_back(-0.5 * length);

mesh->vertices.push_back(-0.5 * width);
mesh->vertices.push_back(0.5 * height);
mesh->vertices.push_back(0.5 * length);

mesh->vertices.push_back(0.5 * width);
mesh->vertices.push_back(0.5 * height);
mesh->vertices.push_back(-0.5 * length);

mesh->vertices.push_back(0.5 * width);
mesh->vertices.push_back(-0.5 * height);
mesh->vertices.push_back(0.5 * length);

mesh->vertices.push_back(0.5 * width);
mesh->vertices.push_back(0.5 * height);
mesh->vertices.push_back(0.5 * length);

// face 1
mesh->indices.push_back(0);
mesh->indices.push_back(1);
mesh->indices.push_back(2);

mesh->indices.push_back(1);
mesh->indices.push_back(2);
mesh->indices.push_back(3);

// face 2
mesh->indices.push_back(2);
mesh->indices.push_back(3);
mesh->indices.push_back(4);

mesh->indices.push_back(3);
mesh->indices.push_back(4);
mesh->indices.push_back(5);

// face 3
mesh->indices.push_back(4);
mesh->indices.push_back(5);
mesh->indices.push_back(6);

mesh->indices.push_back(5);
mesh->indices.push_back(6);
mesh->indices.push_back(7);

// face 4
mesh->indices.push_back(6);
mesh->indices.push_back(7);
mesh->indices.push_back(8);

mesh->indices.push_back(7);
mesh->indices.push_back(8);
mesh->indices.push_back(9);

// face 5
mesh->indices.push_back(8);
mesh->indices.push_back(9);
mesh->indices.push_back(10);

mesh->indices.push_back(9);
mesh->indices.push_back(10);
mesh->indices.push_back(11);

// face 6
mesh->indices.push_back(10);
mesh->indices.push_back(11);
mesh->indices.push_back(12);

mesh->indices.push_back(11);
mesh->indices.push_back(12);
mesh->indices.push_back(13);

return mesh;
}

Mesh::Ptr MeshUtil::generateSphereMesh(double radius, int horizontalSteps, int verticalSteps) {
Mesh::Ptr mesh = std::make_shared<Mesh>();

float thetaStep = 3.14f / (1.0f + horizontalSteps);
float phiStep = 3.14f / (0.5f * verticalSteps);

// setup top tip
mesh->vertices.push_back(0);
mesh->vertices.push_back(radius);
mesh->vertices.push_back(0);

// generate sphere verts
for (int i = 0; i < horizontalSteps; i++) {
    float theta = (i + 1) * thetaStep;
    float y = radius * glm::cos(theta);
    for (int j = 0; j < verticalSteps; j++) {
        float phi = j * phiStep;
        float x = radius * glm::sin(theta) * glm::cos(phi);
        float z = radius * glm::sin(theta) * glm::sin(phi);
        mesh->vertices.push_back(x);
        mesh->vertices.push_back(y);
        mesh->vertices.push_back(z);
    }
}

// setup bottom tip
mesh->vertices.push_back(0);
mesh->vertices.push_back(-radius);
mesh->vertices.push_back(0);

// connect verts with triangle faces
int lastIndex = mesh->vertices.size() / 3 - 1;
// connect bottom and top tips
for (int i = 0; i < verticalSteps; i++) {
    int k = (i + 1) % verticalSteps;
    mesh->indices.push_back(0);
    mesh->indices.push_back(i + 1);
    mesh->indices.push_back(k + 1);

    mesh->indices.push_back(lastIndex);
    mesh->indices.push_back(lastIndex - k - 1);
    mesh->indices.push_back(lastIndex - i - 1);
}

for (int i = 0; i < horizontalSteps - 1; i++) {
    int index = i * verticalSteps + 1;
    for (int j = 0; j < verticalSteps; j++) {
        int k = (j + 1) % verticalSteps;
        mesh->indices.push_back(index + verticalSteps + j);
        mesh->indices.push_back(index + j);
        mesh->indices.push_back(index + k);

        mesh->indices.push_back(index + verticalSteps + k);
        mesh->indices.push_back(index + verticalSteps + j);
        mesh->indices.push_back(index + k);
    }
}

// load verts/indices into mesh buffers
mesh->reload();

return mesh;
}

Mesh::Ptr MeshUtil::generateCylinderMesh(double radius, double length, int lengthSteps, int circumferenceSteps) {
Mesh::Ptr mesh = std::make_shared<Mesh>();

float rStep = length / (1.0 * lengthSteps);
float phiStep = 3.14f / (0.5f * circumferenceSteps);

// setup top cap
mesh->vertices.push_back(0);
mesh->vertices.push_back(-0.5 * length);
mesh->vertices.push_back(0);

// generate cylinder verts
for (int i = 0; i <= lengthSteps; i++) {
    float r = i * rStep - 0.5 * length;
    for (int j = 0; j < circumferenceSteps; j++) {
        float phi = j * phiStep;
        float x = radius * glm::cos(phi);
        float z = radius * glm::sin(phi);
        mesh->vertices.push_back(x);
        mesh->vertices.push_back(r);
        mesh->vertices.push_back(z);
    }
}

// setup bottom cap
mesh->vertices.push_back(0);
mesh->vertices.push_back(0.5 * length);
mesh->vertices.push_back(0);

// connect verts with triangle faces
int lastIndex = mesh->vertices.size() / 3 - 1;
// connect bottom and top tips
for (int i = 0; i < circumferenceSteps; i++) {
    int k = (i + 1) % circumferenceSteps;
    mesh->indices.push_back(0);
    mesh->indices.push_back(i + 1);
    mesh->indices.push_back(k + 1);

    mesh->indices.push_back(lastIndex);
    mesh->indices.push_back(lastIndex - i - 1);
    mesh->indices.push_back(lastIndex - k - 1);
}

for (int i = 0; i < lengthSteps; i++) {
    int index = i * circumferenceSteps + 1;
    for (int j = 0; j < circumferenceSteps; j++) {
        int k = (j + 1) % circumferenceSteps;
        mesh->indices.push_back(index + j);
        mesh->indices.push_back(index + circumferenceSteps + j);
        mesh->indices.push_back(index + circumferenceSteps + k);

        mesh->indices.push_back(index + circumferenceSteps + k);
        mesh->indices.push_back(index + k);
        mesh->indices.push_back(index + j);
    }
}

// load verts/indices into mesh buffers
mesh->reload();

return mesh;
}
*/