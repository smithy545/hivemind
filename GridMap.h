//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_GRIDMAP_H
#define HIVEMIND_GRIDMAP_H


#include <vector>
#include <memory>
#include "Map.h"

class GridMap : public Map {
public:
    GridMap(int width, int height);

    std::vector<MapNode> getNeighbors(MapNode position);
    std::vector<MapNode> getNodes();

    const int &Width() const;
    const int &Height() const;
private:
    const int width;
    const int height;
    std::vector<MapNode> nodes;
};


#endif //HIVEMIND_GRIDMAP_H
