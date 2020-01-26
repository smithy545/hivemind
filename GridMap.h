//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_GRIDMAP_H
#define HIVEMIND_GRIDMAP_H


#include <vector>
#include <memory>

#include "Map.h"
#include "MapNode.h"

class GridMap : public Map {
public:
    typedef std::shared_ptr<GridMap> Ptr;

    GridMap(int width, int height);

    std::vector<MapNode::Ptr> getNodes() override;
    MapNode::Ptr getNode(int x, int y) override;

    int getWidth() const;
    int getHeight() const;
private:
    const int width;
    const int height;
    std::vector<MapNode::Ptr> nodes;
};


#endif //HIVEMIND_GRIDMAP_H
