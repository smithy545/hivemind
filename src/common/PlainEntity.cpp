//
// Created by Philip on 3/21/2020.
//

#include "PlainEntity.h"

#include <utility>


PlainEntity::PlainEntity(json schema) : Entity(std::move(schema)) {}

bool PlainEntity::unpack(json data) {
    if (validate(data)) {
        this->data = data;
        return true;
    }
    return false;
}

json PlainEntity::pack() {
    return data;
}