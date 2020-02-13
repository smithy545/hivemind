//
// Created by Philip on 2/9/2020.
//

#ifndef HIVEMIND_MAPACTOR_H
#define HIVEMIND_MAPACTOR_H

#include <memory>

#include "MapEntity.h"
#include "MapNode.h"


class MapActor : public MapEntity {
public:
    typedef std::shared_ptr<MapActor> Ptr;

    virtual void update() = 0;

    MapNode::MapPath getPath() const {
        return path;
    }
protected:
    MapNode::MapPath path;

    MapActor(MapPosition position, MapNode::MapPath path) : MapEntity(position), path(path) {}
};

#endif //HIVEMIND_MAPACTOR_H
