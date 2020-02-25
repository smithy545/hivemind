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

    enum Action {
        MOVE, IDLE
    };

    virtual Action update(std::shared_ptr<GridMap> map) = 0;

    void addToPath(MapNode::Ptr nextPos);

    void addToPath(const MapNode::MapPath &next);

    void setPath(const MapNode::MapPath &path);

    const MapNode::MapPath &getPath() const {
        return path;
    }

protected:
    MapNode::MapPath path;

    MapActor();

    explicit MapActor(const MapNode::Ptr &initialLocation);

    explicit MapActor(MapNode::MapPath initialPath);

    MapActor(const MapNode::Ptr &initialLocation, MapNode::MapPath initialPath);
};

#endif //HIVEMIND_MAPACTOR_H
