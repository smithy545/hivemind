//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_GRIDMAP_H
#define HIVEMIND_GRIDMAP_H


#include <vector>
#include <memory>
#include "MapNode.h"

class GridMap {
public:
    typedef std::shared_ptr<GridMap> Ptr;

    GridMap(int width, int height);

    std::vector<MapNode::Ptr> getNodes();
    MapNode::Ptr getNode(int x, int y);

    const int &Width() const;
    const int &Height() const;
private:
    const int width;
    const int height;
    std::vector<MapNode::Ptr> nodes;
};


#endif //HIVEMIND_GRIDMAP_H
