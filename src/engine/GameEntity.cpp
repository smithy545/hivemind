//
// Created by Philip on 6/2/2020.
//

#include "GameEntity.h"

#include <utility>

GameEntity::GameEntity(const Bound::Ptr &bound, Body::Ptr body) : amnioticBound(bound), bound(bound), body(std::move(body)) {}

const Bound::Ptr &GameEntity::getAmnioticBound() const {
    return amnioticBound;
}

const Bound::Ptr &GameEntity::getBound() const {
    return bound;
}

const Body::Ptr &GameEntity::getBody() const {
    return body;
}

const std::vector<GameEntity::Ptr> &GameEntity::getChildren() const {
    return children;
}
