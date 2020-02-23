//
// Created by Philip on 2/9/2020.
//

#ifndef HIVEMIND_MAPENTITY_H
#define HIVEMIND_MAPENTITY_H

#include <memory>

#include "MapPosition.h"


class MapEntity {
public:
    typedef std::shared_ptr<MapEntity> Ptr;

    const MapPosition &getPosition() const {
        return position;
    }
protected:
    MapPosition position;

    explicit MapEntity(MapPosition position) : position(position) {}
};

#endif //HIVEMIND_MAPENTITY_H
