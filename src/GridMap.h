//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_GRIDMAP_H
#define HIVEMIND_GRIDMAP_H

#include <memory>
#include <vector>

#include "MapActor.h"
#include "MapNode.h"
#include "Mesh.h"
#include "WorldMap.h"


class GridMap : public WorldMap {
public:
    typedef std::shared_ptr<GridMap> Ptr;

    GridMap(int width, int height);

    // topology
    std::vector<MapNode::Ptr> &getNodes() override {
        return nodes;
    }

    MapNode::Ptr getNode(int x, int y) override;

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    // world interaction
    const std::vector<MapActor::Ptr> &getActors() override {
        return actors;
    }

    void addActor(MapActor::Ptr actor, int x, int y) override;

    bool moveActor(std::weak_ptr<MapActor> actor, std::weak_ptr<MapNode> nextPos) override;

    // rendering
    Mesh::Ptr generateMesh(float screenWidth, float screenHeight, float tileSize);

private:
    const int width;
    const int height;
    std::vector<MapNode::Ptr> nodes;

    std::vector<MapActor::Ptr> actors;

    Mesh::Ptr mesh;
    float *vertices{nullptr};
    unsigned int *indices{nullptr};
};


#endif //HIVEMIND_GRIDMAP_H
