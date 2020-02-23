//
// Created by Philip on 2/23/2020.
//

#ifndef HIVEMIND_STRUCTURENODE_H
#define HIVEMIND_STRUCTURENODE_H

#include <algorithm>
#include <utility>
#include <vector>

#include "MapNode.h"
#include "Structure.h"


class StructureNode : public MapNode {
public:
    Structure::Ptr structure;

    // Construct from scratch
    StructureNode(int x, int y) : MapNode(x, y), width(1), height(1) {}
    StructureNode(int x, int y, bool passable) : MapNode(x, y, passable), width(1), height(1) {}
    StructureNode(int x, int y, int width, int height) : MapNode(x, y), width(width), height(height) {}
    StructureNode(int x, int y, int width, int height, bool passable) : MapNode(x, y, passable), width(width), height(height) {}

    // Construct and inject into map
    StructureNode(const MapNode& position, bool passable) : StructureNode(position.x, position.y) {
        for(auto neighbor: position.neighbors)
            neighbors.push_back(neighbor);
    }

    // First node is used as "anchor" node
    explicit StructureNode(std::vector<MapNode::Ptr> nodes) : StructureNode(std::move(nodes), false) {}
    StructureNode(std::vector<MapNode::Ptr> nodes, bool passable) : MapNode(nodes[0]->x, nodes[0]->y, passable) {
        int minX = x;
        int minY = y;
        int maxX = x;
        int maxY = y;
        for(const auto& node: nodes) {
            if(minX > node->x) {
                minX = node->x;
            }
            if(maxX < node->x) {
                maxX = node->x;
            }
            if(minY > node->y) {
                minY = node->y;
            }
            if(maxY < node->y) {
                maxY = node->y;
            }
        }
        width = maxX - minX + 1;
        height = maxY - minY + 1;

        // add neighbors
        for(const auto& node: nodes) {
            for(auto neighbor: node->neighbors) {
                if(isNeighbor(neighbor)) {
                    neighbors.push_back(neighbor);
                    // replace neighbors reference to previous MapNode with this StructureNode
                    for(int i = 0; i < neighbor->neighbors.size(); i++) {
                        if(neighbor->neighbors[i] == node) {
                            neighbor->neighbors[i] = std::shared_ptr<StructureNode>(this);
                            break;
                        }
                    }
                }
            }
        }
    }

    int width;
    int height;
private:
    bool isNeighbor(Ptr node) {
        return node->x == x - 1 || node->x == x + width || node->y == y - 1 || node->y == y + height;
    }
};


#endif //HIVEMIND_STRUCTURENODE_H
