//
// Created by philip on 1/23/20.
//

#include "GridMap.h"

GridMap::GridMap(int width, int height) : width(width), height(height) {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            MapNode::Ptr node = std::make_shared<MapNode>(x, y);
            const bool xgt0 = x > 0;
            const bool ygt0 = y > 0;
            const bool xltw = x < width - 1;
            const bool ylth = y < height - 1;
            if(xgt0)
                node->neighbors.push_back(nodes[y*width + x - 1]);
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
            nodes.push_back(node);
        }
    }
}

std::vector<MapNode::Ptr> GridMap::getNodes() {
    return nodes;
}

MapNode::Ptr GridMap::getNode(int x, int y) {
    int index = y*width + x;
    if(index < 0 || index > nodes.size())
        return nullptr;
    return nodes[index];
}

int GridMap::getWidth() const {
    return width;
}

int GridMap::getHeight() const {
    return height;
}