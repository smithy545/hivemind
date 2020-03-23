//
// Created by Philip on 2/23/2020.
//

#include "WorldActor.h"

#include <utility>

/*
WorldActor::WorldActor(std::string spriteName) : WorldEntity(std::move(spriteName)) {}

WorldActor::WorldActor(std::string spriteName, const MapNode::Ptr &initialLocation) : WorldEntity(std::move(spriteName),
                                                                                                  initialLocation) {}

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
*/