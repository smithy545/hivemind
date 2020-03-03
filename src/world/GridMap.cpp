//
// Created by philip on 1/23/20.
//

#include "GridMap.h"

#include <iostream>

#include "Human.h"


GridMap::GridMap(int width, int height) : width(width), height(height) {
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
            if (xltw)
                node->getNeighbors().insert(nodes[index + 1]);
            if (ygt0)
                node->getNeighbors().insert(nodes[index - width]);
            if (ylth)
                node->getNeighbors().insert(nodes[index + width]);
            if (xgt0 && ygt0)
                node->getNeighbors().insert(nodes[index - width - 1]);
            if (xltw && ylth)
                node->getNeighbors().insert(nodes[index + width + 1]);
            if (xgt0 && ylth)
                node->getNeighbors().insert(nodes[index + width - 1]);
            if (xltw && ygt0)
                node->getNeighbors().insert(nodes[index - width + 1]);
        }
    }
}

MapNode::Ptr GridMap::getNode(int x, int y) {
    unsigned int index = y * width + x;
    if (x >= width || y >= height || x < 0 || y < 0)
        return nullptr;
    return nodes[index];
}

bool GridMap::addEntity(WorldEntity::Ptr entity, int x, int y) {
    MapNode::Ptr node = getNode(x, y);
    if (node != nullptr && node->isPassable()) {
        std::cout << "Adding entity " << entity->getIdString() << std::endl;

        // node->addEntity(entitiy.id, entitiy)
        node->setPassable(false);
        entity->setPosition(node);

        entities.push_back(entity);

        return true;
    }
    return false;
}

bool GridMap::addActor(WorldActor::Ptr actor, int x, int y) {
    if (addEntity(actor, x, y)) {
        actors.push_back(actor);
        return true;
    }
    return false;
}

bool GridMap::moveEntity(std::weak_ptr<WorldEntity> entityPtr, std::weak_ptr<MapNode> nextPosPtr) {
    WorldEntity::Ptr entity = entityPtr.lock();
    MapNode::Ptr nextPos = nextPosPtr.lock();

    if (!nextPos->isPassable())
        return false;

    // create MapNode object for actor if it doesn't have one
    if (entity->getPosition() == nullptr) {
        entity->setPosition(nextPos);
        //nextPos->addEntity(entity->getUId(), entity);

        return true;
    } else {
        // verify that we're moving the actor to neighboring location
        for (const MapNode::Ptr &neighbor: entity->getPosition()->getNeighbors()) {
            if (nextPos == neighbor) {

                // unlink from existing node
                entity->getPosition()->setPassable(true);
                //entity->getPosition()->removeEntity(entity->getIdString());

                // link to next pos node
                entity->setPosition(nextPos);
                //nextPos->addEntity(entity->getUId(), entity);
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
            //node->addEntity(structure->getUId(), structure);
            node->setPassable(false);
            node->setType(MapNode::STRUCTURE);
        }
    }
    auto anchorNode = getNode(x, y);
    structure->setPosition(anchorNode);
    entities.push_back(structure);
    return true;
}
