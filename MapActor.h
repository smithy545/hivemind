//
// Created by Philip on 2/9/2020.
//

#ifndef HIVEMIND_MAPACTOR_H
#define HIVEMIND_MAPACTOR_H

#include <memory>
#include <utility>

#include "MapEntity.h"
#include "MapNode.h"


class MapActor : public MapEntity {
public:
    typedef std::shared_ptr<MapActor> Ptr;

    virtual void update() = 0;

    void addToPath(const MapNode::Ptr& nextPos);

    const MapNode::MapPath &getPath() const {
        return path;
    }

protected:
    MapNode::MapPath path;

    MapActor() : MapEntity() {}
    MapActor(MapNode::MapPath path) : MapEntity(), path(std::move(path)) {}
};

#endif //HIVEMIND_MAPACTOR_H
