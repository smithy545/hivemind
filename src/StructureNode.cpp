//
// Created by Philip on 2/23/2020.
//

#include "StructureNode.h"

// Construct from scratch
StructureNode::StructureNode(int x, int y) : MapNode(x, y), width(1), height(1) {}
StructureNode::StructureNode(int x, int y, bool passable) : MapNode(x, y, passable), width(1), height(1) {}
StructureNode::StructureNode(int x, int y, int width, int height) : MapNode(x, y), width(width), height(height) {}
StructureNode::StructureNode(int x, int y, int width, int height, bool passable)
: MapNode(x, y, passable), width(width), height(height) {}

// Construct and inject into map

StructureNode::StructureNode(const MapNode::Ptr &position, bool passable) : StructureNode(position->getX(),
                                                                                          position->getY()) {
    for (const auto &neighbor: position->getNeighbors())
        getNeighbors().insert(neighbor);
}

// First node is used as "anchor" node
StructureNode::StructureNode(std::vector<MapNode::Ptr> nodes) : StructureNode(std::move(nodes), false) {}

StructureNode::StructureNode(std::vector<MapNode::Ptr> nodes, bool passable)
        : MapNode(nodes[0]->getX(), nodes[0]->getY(), passable) {
    int minX = getX();
    int minY = getY();
    int maxX = getX();
    int maxY = getY();
    for (const auto &node: nodes) {
        if (minX > node->getX()) {
            minX = node->getX();
        }
        if (maxX < node->getX()) {
            maxX = node->getX();
        }
        if (minY > node->getY()) {
            minY = node->getY();
        }
        if (maxY < node->getY()) {
            maxY = node->getY();
        }
    }
    width = maxX - minX + 1;
    height = maxY - minY + 1;

    // add neighbors
    for(const auto& node: nodes) {
        for (const auto &neighbor: node->getNeighbors()) {
            if (isNeighbor(neighbor)) {
                // replace neighbors reference to previous MapNode with this StructureNode
                getNeighbors().insert(neighbor);
                neighbor->getNeighbors().erase(node);
            }
        }
    }
}

bool StructureNode::isNeighbor(const MapNode::Ptr& node) {
    return node->getX() == getX() - 1 || node->getX() == getX() + width || node->getY() == getY() - 1 ||
           node->getY() == getY() + height;
}