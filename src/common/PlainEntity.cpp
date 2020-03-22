//
// Created by Philip on 3/21/2020.
//

#include "PlainEntity.h"


PlainEntity::PlainEntity(const json &schema) : Entity(schema) {}

json PlainEntity::pack() {
    return data;
}

bool PlainEntity::unpack(json data) {
    if (validate(data)) {
        this->data = data;
        return true;
    }
    return false;
}
