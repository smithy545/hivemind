//
// Created by Philip on 2/9/2020.
//

#ifndef HIVEMIND_MAPACTOR_H
#define HIVEMIND_MAPACTOR_H

#include <memory>
#include <utility>

#include "MapEntity.h"
#include "MapNode.h"

class GridMap;

class MapActor : public MapEntity, public std::enable_shared_from_this<MapActor> {
public:
    typedef std::shared_ptr<MapActor> Ptr;

    virtual void update(std::shared_ptr<GridMap> map) = 0;

    void addToPath(MapNode::Ptr nextPos);

    const MapNode::MapPath &getPath() const {
        return path;
    }

protected:
    MapNode::MapPath path;

    MapActor() : MapEntity() {}
    explicit MapActor(MapNode::MapPath path) : MapEntity(), path(std::move(path)) {}
};

#endif //HIVEMIND_MAPACTOR_H
