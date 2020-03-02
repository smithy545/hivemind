//
// Created by Philip on 2/9/2020.
//

#ifndef HIVEMIND_WORLDACTOR_H
#define HIVEMIND_WORLDACTOR_H

#include <memory>
#include <utility>

#include "WorldEntity.h"
#include "src/pathing/MapNode.h"

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

#endif //HIVEMIND_WORLDACTOR_H
