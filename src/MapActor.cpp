//
// Created by Philip on 2/23/2020.
//


#include "MapActor.h"

#include <utility>

MapActor::MapActor() : MapEntity() {}

MapActor::MapActor(const MapNode::Ptr &initialLocation) : MapEntity(initialLocation) {}

MapActor::MapActor(MapNode::MapPath initialPath) : MapActor(nullptr, std::move(initialPath)) {}

MapActor::MapActor(const MapNode::Ptr &initialLocation, MapNode::MapPath initialPath) : MapEntity(initialLocation),
                                                                                        path(std::move(initialPath)) {}

void MapActor::addToPath(MapNode::Ptr nextPos) {
    path.push_front(std::move(nextPos));
}

void MapActor::addToPath(const MapNode::MapPath &next) {
    for (auto step: next)
        path.push_front(std::move(step));
}

void MapActor::setPath(const MapNode::MapPath &path) {
    MapActor::path = path;
}
