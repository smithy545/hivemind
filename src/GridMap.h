//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_GRIDMAP_H
#define HIVEMIND_GRIDMAP_H


#include <vector>
#include <memory>

#include "GroundNode.h"
#include "Map.h"
#include "MapActor.h"
#include "MapNode.h"


class GridMap : public Map {
public:
    typedef std::shared_ptr<GridMap> Ptr;

    GridMap(int width, int height);

    Mesh::Ptr generateMesh(float screenWidth, float screenHeight, float tileSize) override;
    MapNode::Ptr getNode(int x, int y) override;

    void addActor(MapActor::Ptr actor, int x, int y);
    bool moveActor(std::weak_ptr<MapActor> actor, MapNode::Ptr nextPos) override;

    const std::vector<MapActor::Ptr> &getActors() override {
        return actors;
    }

    const std::vector<MapNode::Ptr> &getNodes() override {
        return nodes;
    }

    const int &getWidth() const {
        return width;
    }

    const int &getHeight() const {
        return height;
    }

private:
    const int width;
    const int height;
    std::vector<MapActor::Ptr> actors;
    std::vector<MapNode::Ptr> nodes;
    Mesh::Ptr mesh;
    float* vertices{nullptr};
    unsigned int* indices{nullptr};
};


#endif //HIVEMIND_GRIDMAP_H