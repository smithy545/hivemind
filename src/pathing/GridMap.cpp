//
// Created by philip on 1/23/20.
//

#include "GridMap.h"

#include <iostream>



GridMap::GridMap(int width, int height) : width(width), height(height), mesh(nullptr) {
    // initialize
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            nodes.push_back(std::make_shared<MapNode>(x, y));
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
                node->getNeighbors().insert(nodes[index - 1]);
            if(xltw)
                node->getNeighbors().insert(nodes[index + 1]);
            if(ygt0)
                node->getNeighbors().insert(nodes[index - width]);
            if(ylth)
                node->getNeighbors().insert(nodes[index + width]);
            if(xgt0 && ygt0)
                node->getNeighbors().insert(nodes[index - width - 1]);
            if(xltw && ylth)
                node->getNeighbors().insert(nodes[index + width + 1]);
            if(xgt0 && ylth)
                node->getNeighbors().insert(nodes[index + width - 1]);
            if(xltw && ygt0)
                node->getNeighbors().insert(nodes[index - width + 1]);
        }
    }
}

MapNode::Ptr GridMap::getNode(int x, int y) {
    unsigned int index = y * width + x;
    if(index < 0 || index >= nodes.size())
        return nullptr;
    return nodes[index];
}

bool GridMap::addEntity(MapEntity::Ptr entity, int x, int y) {
    MapNode::Ptr node = getNode(x, y);
    if (node != nullptr && node->isPassable()) {
        std::cout << "Adding entity " << entity->getUId() << std::endl;
        node->addEntity(entity->getUId(), entity);
        node->setPassable(false);
        entity->setMapNode(node);
        entities.push_back(entity);
        return true;
    }
    return false;
}

bool GridMap::addActor(MapActor::Ptr actor, int x, int y) {
    if (addEntity(actor, x, y)) {
        actors.push_back(actor);
        return true;
    }
    return false;
}

bool GridMap::moveEntity(std::weak_ptr<MapEntity> entityPtr, std::weak_ptr<MapNode> nextPosPtr) {
    MapEntity::Ptr entity = entityPtr.lock();
    MapNode::Ptr nextPos = nextPosPtr.lock();

    if (!nextPos->isPassable())
        return false;

    // create MapNode object for actor if it doesn't have one
    if (entity->getMapNode() == nullptr) {
        entity->setMapNode(nextPos);
        nextPos->addEntity(entity->getUId(), entity);

        return true;
    } else {
        // verify that we're moving the actor to neighboring location
        for (const MapNode::Ptr &neighbor: entity->getPosition()->getNode()->getNeighbors()) {
            if (nextPos == neighbor) {

                // unlink from existing node
                entity->getMapNode()->setPassable(true);
                entity->getMapNode()->removeEntity(entity->getUId());

                // link to next pos node
                entity->setMapNode(nextPos);
                nextPos->addEntity(entity->getUId(), entity);
                nextPos->setPassable(false);

                return true;
            }
        }
    }

    return false;
}

bool GridMap::placeStructure(Structure::Ptr structure, int x, int y, int width, int height) {
    for (int j = y; j < y + height; j++) {
        for (int i = x; i < x + width; i++) {
            auto node = getNode(i, j);
            node->addEntity(structure->getUId(), structure);
            node->setPassable(false);
            node->setType(MapNode::STRUCTURE);
        }
    }
    auto anchorNode = getNode(x, y);
    structure->setMapNode(anchorNode);
    entities.push_back(structure);
    return true;
}

Mesh::Ptr GridMap::generateMesh(float screenWidth, float screenHeight, float tileSize) {
    if (mesh == nullptr) {
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
    }
    int i = 0;
    int j = 0;
    for (const MapEntity::Ptr &entity: toRender) {
        float x = entity->getPosition()->getNode()->getX() * tileSize - screenWidth;
        float y = entity->getPosition()->getNode()->getY() * tileSize - screenHeight;

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
    // clear toRender for next update
    toRender.clear();

    mesh->setNumVertices(i);
    mesh->setNumIndices(j);

    // TODO: selectively call glBufferSubdata on vertices that change, i.e. individual actor meshes

    // load vertex data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBufferId());
    glBufferData(GL_ARRAY_BUFFER, mesh->getNumVertices() * sizeof(float), vertices, GL_STATIC_DRAW);

    // load index data into buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getElementBufferId());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getNumIndices() * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    return mesh;
}

void GridMap::markForRendering(const MapEntity::Ptr &entity) {
    toRender.push_back(entity);
}
