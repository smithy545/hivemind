//
// Created by smith on 3/23/2020.
//

#ifndef SOCIETY_ACTOR_H
#define SOCIETY_ACTOR_H

#include "SchemaEntity.h"


class Actor : public SchemaEntity {
public:
    virtual void update() = 0;
};


#endif //SOCIETY_ACTOR_H
