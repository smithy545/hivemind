//
// Created by Philip on 3/21/2020.
//

#include "PlainEntity.h"

#include <utility>


PlainEntity::PlainEntity(json schema) : Entity(std::move(schema)) {}

bool PlainEntity::unpack(json data) {
    this->data = data;
    return true;
}

json PlainEntity::pack() {
    return data;
}