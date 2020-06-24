//
// Created by smith on 4/9/2020.
//

#include "GridMap.h"


GridMap::GridMap(int width, int height) : GridMap(0, 0, width, height) {}

GridMap::GridMap(int x_offset, int y_offset, int width, int height) : Map(x_offset, y_offset),
                                                                    _width(width),
                                                                    _height(height) {
    // initialize nodes
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            _nodes.push_back(std::make_shared<GridNode>(x_offset + x, y_offset + y));
        }
    }
}

MapNode::Ptr GridMap::get_node(int x, int y) {
    y -= get_y_offset();
    x -= get_x_offset();
    if (x < 0 || y < 0 || x >= _width || y >= _height)
        return nullptr;
    return _nodes[x + y * _width];
}

std::vector<MapNode::Ptr> GridMap::get_neighbors(MapNode::Ptr node) {
    int neighborMatrix[8][2] = {
            {-1, -1},
            {0,  -1},
            {1,  -1},
            {-1, 0},
            {1,  0},
            {-1, 1},
            {0,  1},
            {1,  1},
    };
    int nx = node->get_x();
    int ny = node->get_y();
    std::vector<MapNode::Ptr> neighbors;

    for (auto pos: neighborMatrix) {
        auto neighbor = get_node(nx + pos[0], ny + pos[1]);
        if (neighbor != nullptr)
            neighbors.push_back(neighbor);
    }

    return neighbors;
}
