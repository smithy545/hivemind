//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_GRIDMAP_H
#define HIVEMIND_GRIDMAP_H

#include <memory>
#include <vector>

#include "MapNode.h"
#include "src/render/Mesh.h"
#include "src/world/MapActor.h"
#include "src/world/MapEntity.h"
#include "src/world/Structure.h"
#include "src/world/WorldMap.h"


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
    const std::vector<MapEntity::Ptr> &getEntities() override {
        return entities;
    }

    const std::vector<MapActor::Ptr> &getActors() override {
        return actors;
    }

    bool addEntity(MapEntity::Ptr entity, int x, int y) override;

    bool addActor(MapActor::Ptr actor, int x, int y) override;

    bool moveEntity(std::weak_ptr<MapEntity> entity, std::weak_ptr<MapNode> nextPos) override;

    bool placeStructure(Structure::Ptr structure, int x, int y, int width, int height) override;

    // rendering
    Mesh::Ptr generateMesh(float screenWidth, float screenHeight, float tileSize);

    void markForRendering(const MapEntity::Ptr &entity);

private:
    const int width;
    const int height;
    std::vector<MapNode::Ptr> nodes;
    std::vector<MapEntity::Ptr> entities;
    std::vector<MapActor::Ptr> actors;

    std::vector<MapEntity::Ptr> toRender;

    Mesh::Ptr mesh;
    float *vertices{nullptr};
    unsigned int *indices{nullptr};
};


#endif //HIVEMIND_GRIDMAP_H
