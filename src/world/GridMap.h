//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_GRIDMAP_H
#define HIVEMIND_GRIDMAP_H

#include <memory>
#include <vector>

#include "pathing/MapNode.h"

#include "Structure.h"
#include "WorldActor.h"
#include "WorldEntity.h"
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
    const std::vector<WorldEntity::Ptr> &getEntities() override {
        return entities;
    }

    const std::vector<WorldActor::Ptr> &getActors() override {
        return actors;
    }

    bool addEntity(WorldEntity::Ptr entity, int x, int y) override;

    bool addActor(WorldActor::Ptr actor, int x, int y) override;

    bool moveEntity(std::weak_ptr<WorldEntity> entity, std::weak_ptr<MapNode> nextPos) override;

    bool placeStructure(Structure::Ptr structure, int x, int y, int width, int height) override;

private:
    const int width;
    const int height;
    std::vector<MapNode::Ptr> nodes;
    std::vector<WorldEntity::Ptr> entities;
    std::vector<WorldActor::Ptr> actors;

};


#endif //HIVEMIND_GRIDMAP_H
