//
// Created by Philip on 2/24/2020.
//

#ifndef HIVEMIND_WORLDMAP_H
#define HIVEMIND_WORLDMAP_H

#include <memory>
#include <vector>

#include "Map.h"
#include "MapActor.h"
#include "MapNode.h"


class WorldMap : public Map {
public:
    typedef std::shared_ptr<WorldMap> Ptr;

    virtual const std::vector<MapActor::Ptr> &getActors() = 0;

    virtual void addActor(MapActor::Ptr actor, int x, int y) = 0;

    virtual bool moveActor(std::weak_ptr<MapActor> actor, std::weak_ptr<MapNode> nextPos) = 0;
};

#endif //HIVEMIND_WORLDMAP_H
