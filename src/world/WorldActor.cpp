//
// Created by Philip on 2/23/2020.
//


#include "WorldActor.h"


WorldActor::WorldActor() : WorldEntity() {}

WorldActor::WorldActor(const MapNode::Ptr &initialLocation) : WorldEntity(initialLocation) {}

void WorldActor::addToPath(MapNode::Ptr nextPos) {
    path.push_front(std::move(nextPos));
}

void WorldActor::addToPath(const MapNode::MapPath &next) {
    for (auto step: next)
        path.push_front(std::move(step));
}

const MapNode::MapPath &WorldActor::getPath() const {
    return path;
}

void WorldActor::setPath(const MapNode::MapPath &path) {
    this->path = path;
}
