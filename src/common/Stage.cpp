//
// Created by smith on 3/23/2020.
//

#include "Stage.h"

#include <utility>


json Stage::get(unsigned int id) {
    if (entities.find(id) != entities.end())
        return entities[id];
    return {};
}

void Stage::put(unsigned int id, json entity) {
    entities[id] = std::move(entity);
}