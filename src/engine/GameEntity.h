//
// Created by Philip on 6/2/2020.
//

#ifndef SOCIETY_GAMEENTITY_H
#define SOCIETY_GAMEENTITY_H

#include <vector>

#include "collision/Body.h"
#include "collision/Bound.h"
#include "macros.h"


class GameEntity {
public:
    POINTERIZE(GameEntity);

    GameEntity(const Bound::Ptr &bound, Body::Ptr body);

    const Bound::Ptr &getAmnioticBound() const;

    const Bound::Ptr &getBound() const;

    const Body::Ptr &getBody() const;

    const std::vector<Ptr> &getChildren() const;
private:
    Bound::Ptr amnioticBound; // bound of object on inception
    Bound::Ptr bound;         // current bound of object
    Body::Ptr body;
    std::vector<Ptr> children;
};


#endif //SOCIETY_GAMEENTITY_H
