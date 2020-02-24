//
// Created by philip on 1/23/20.
//

#include "GridMap.h"

#include <iostream>


GridMap::GridMap(int width, int height) : width(width), height(height), mesh(nullptr) {
    // initialize
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            nodes.push_back(std::make_shared<GroundNode>(x, y));
        }
    }
    // setup topology
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * width + x;
            MapNode::Ptr node = nodes[index];
            const bool xgt0 = x > 0;
            const bool ygt0 = y > 0;
            const bool xltw = x < width - 1;
            const bool ylth = y < height - 1;
            if (xgt0)
                node->neighbors.push_back(nodes[index - 1]);
            if(xltw)
                node->neighbors.push_back(nodes[index + 1]);
            if(ygt0)
                node->neighbors.push_back(nodes[index - width]);
            if(ylth)
                node->neighbors.push_back(nodes[index + width]);
            if(xgt0 && ygt0)
                node->neighbors.push_back(nodes[index - width - 1]);
            if(xltw && ylth)
                node->neighbors.push_back(nodes[index + width + 1]);
            if(xgt0 && ylth)
                node->neighbors.push_back(nodes[index + width - 1]);
            if(xltw && ygt0)
                node->neighbors.push_back(nodes[index - width + 1]);
        }
    }
}

MapNode::Ptr GridMap::getNode(int x, int y) {
    unsigned int index = y * width + x;
    if(index < 0 || index >= nodes.size())
        return nullptr;
    return nodes[index];
}

Mesh::Ptr GridMap::generateMesh(float screenWidth, float screenHeight, float tileSize) {
    if (mesh == nullptr) {
        int N = nodes.size();

        // set size to max possible visible
        vertices = new float[8 * N];
        indices = new unsigned int[6 * N];
        mesh = std::make_shared<Mesh>(8*N, 6*N);

        glBindVertexArray(mesh->vertexArrayId);
        glEnableVertexAttribArray(0);

        // load vertex data into buffer
        glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBufferId);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        // load index data into buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementBufferId);
    }
    int i = 0;
    int j = 0;
    for (const MapActor::Ptr& actor: actors) {
        float x = actor->getPosition()->node->x * tileSize - screenWidth;
        float y = actor->getPosition()->node->y * tileSize - screenHeight;

        // top right
        vertices[i] = x / screenWidth;
        vertices[i + 1] = (y + tileSize) / screenHeight;
        // bottom right
        vertices[i + 2] = x / screenWidth;
        vertices[i + 3] = y / screenHeight;
        // bottom left
        vertices[i + 4] = (x + tileSize) / screenWidth;
        vertices[i + 5] = y / screenHeight;
        // top left
        vertices[i + 6] = (x + tileSize) / screenWidth;
        vertices[i + 7] = (y + tileSize) / screenHeight;

        // two triangles that make a square at the given tile location
        indices[j] = i / 2;
        indices[j + 1] = i / 2 + 1;
        indices[j + 2] = i / 2 + 3;
        indices[j + 3] = i / 2 + 1;
        indices[j + 4] = i / 2 + 2;
        indices[j + 5] = i / 2 + 3;

        i += 8;
        j += 6;
    }
    mesh->numVertices = i;
    mesh->numIndices = j;

    // TODO: selectively call glBufferSubdata on vertices that change, i.e. individual actor meshes

    // load vertex data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, mesh->numVertices * sizeof(float), vertices, GL_STATIC_DRAW);

    // load index data into buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    return mesh;
}

void GridMap::addActor(MapActor::Ptr actor, int x, int y) {
    MapNode::Ptr node = getNode(x, y);
    node->entities[actor->getUId()] = actor;
    actor->setPosition(std::make_shared<MapPosition>(node));
    actors.push_back(actor);
}

bool GridMap::moveActor(std::weak_ptr<MapActor> actor, MapNode::Ptr nextPos) {
    // TODO: use weak_ptr for nextPos and move this null check out of moveActor
    // AKA start coding properly at some point instead of hackily... lol
    if(nextPos == nullptr)
        return false;

    std::shared_ptr<MapActor> ptr = actor.lock();

    // create MapPosition object for actor if it doesn't have one
    if(ptr->getPosition() == nullptr) {
        ptr->setPosition(std::make_shared<MapPosition>(nextPos));
        nextPos->entities[ptr->getUId()] = ptr;

        return true;
    } else if(ptr->getPosition()->node != nullptr){
        // verify that we're moving the actor to neighboring location
        for(MapNode::Ptr neighbor: ptr->getPosition()->node->neighbors) {
            if(nextPos == neighbor) {

                // unlink from existing node
                ptr->getPosition()->node->entities.erase(ptr->getUId());

                // link to next pos node
                ptr->getPosition()->node = nextPos;
                nextPos->entities[ptr->getUId()] = ptr;

                return true;
            }
        }
    } else {
        ptr->getPosition()->node = nextPos;
        nextPos->entities[ptr->getUId()] = ptr;
        return true;
    }

    return false;
}
