//
// Created by Philip on 3/21/2020.
//

#ifndef SOCIETY_PLAINENTITY_H
#define SOCIETY_PLAINENTITY_H

#include "Entity.h"


class PlainEntity : public Entity {
public:
    explicit PlainEntity(json schema);

    bool unpack(json data) override;

    json pack() override;

private:
    json data;
};


#endif //SOCIETY_PLAINENTITY_H
