//
// Created by Philip on 2/9/2020.
//

#ifndef SOCIETY_WORLDACTOR_H
#define SOCIETY_WORLDACTOR_H

#include <memory>
#include <utility>

#include "pathing/MapNode.h"

#include "WorldEntity.h"


class GridMap;


class WorldActor : public WorldEntity, public std::enable_shared_from_this<WorldActor> {
public:
    typedef std::shared_ptr<WorldActor> Ptr;

    enum Action {
        MOVE, IDLE
    };

    virtual Action update(std::shared_ptr<GridMap> map) = 0;

    void addToPath(MapNode::Ptr nextPos);

    void addToPath(const MapNode::MapPath &next);

    const MapNode::MapPath &getPath() const;

    void setPath(const MapNode::MapPath &path);

protected:
    MapNode::MapPath path;

    WorldActor();

    explicit WorldActor(const MapNode::Ptr &initialLocation);
};

#endif //SOCIETY_WORLDACTOR_H
