//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_GRIDMAP_H
#define HIVEMIND_GRIDMAP_H


#include <vector>
#include <memory>

#include "Map.h"
#include "MapActor.h"
#include "MapNode.h"


class GridMap : public Map {
public:
    typedef std::shared_ptr<GridMap> Ptr;

    GridMap(int width, int height);

    Mesh::Ptr generateMesh(float screenWidth, float screenHeight, float tilesize) override;

    MapNode::Ptr getNode(int x, int y) override;

    std::vector<MapActor::Ptr> getActors() override {
        return actors;
    }

    std::vector<MapNode::Ptr> getNodes() override {
        return nodes;
    }

    const int &Width() const {
        return width;
    }
    const int &Height() const {
        return height;
    }
private:
    const int width;
    const int height;
    std::vector<MapActor::Ptr> actors;
    std::vector<MapNode::Ptr> nodes;
    Mesh::Ptr mesh;
};


#endif //HIVEMIND_GRIDMAP_H
