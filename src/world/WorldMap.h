//
// Created by Philip on 2/24/2020.
//

#ifndef SOCIETY_WORLDMAP_H
#define SOCIETY_WORLDMAP_H

#include <memory>
#include <pathing/Map.h>
#include <pathing/MapNode.h>
#include <vector>

#include "WorldActor.h"


class WorldMap : public Map {
public:
    typedef std::shared_ptr<WorldMap> Ptr;

    virtual const std::vector<WorldActor::Ptr> &getActors() = 0;

    virtual const std::vector<WorldEntity::Ptr> &getEntities() = 0;

    //virtual bool addEntity(WorldEntity::Ptr entity, int x, int y) = 0;

    //virtual bool moveEntity(std::weak_ptr<WorldEntity> entity, std::weak_ptr<MapNode> nextPos) = 0;

    //virtual bool addActor(WorldActor::Ptr actor, int x, int y) = 0;

    //virtual bool placeStructure(Structure::Ptr structure, int x, int y, int width, int height) = 0;
};

#endif //SOCIETY_WORLDMAP_H
