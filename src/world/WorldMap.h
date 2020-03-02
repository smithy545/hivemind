//
// Created by Philip on 2/24/2020.
//

#ifndef HIVEMIND_WORLDMAP_H
#define HIVEMIND_WORLDMAP_H

#include <memory>
#include <vector>

#include "src/pathing/Map.h"
#include "src/world/WorldActor.h"
#include "src/pathing/MapNode.h"
#include "Structure.h"

class WorldMap : public Map {
public:
    typedef std::shared_ptr<WorldMap> Ptr;

    virtual const std::vector<WorldActor::Ptr> &getActors() = 0;

    virtual const std::vector<WorldEntity::Ptr> &getEntities() = 0;

    virtual bool addEntity(WorldEntity::Ptr entity, int x, int y) = 0;

    virtual bool moveEntity(std::weak_ptr<WorldEntity> entity, std::weak_ptr<MapNode> nextPos) = 0;

    virtual bool addActor(WorldActor::Ptr actor, int x, int y) = 0;

    virtual bool placeStructure(Structure::Ptr structure, int x, int y, int width, int height) = 0;
};

#endif //HIVEMIND_WORLDMAP_H
