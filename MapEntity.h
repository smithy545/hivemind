//
// Created by Philip on 2/9/2020.
//

#ifndef HIVEMIND_MAPENTITY_H
#define HIVEMIND_MAPENTITY_H

#include <memory>
#include <string>
#include <utility>

#include "MapPosition.h"


class MapEntity {
public:
    static int GLOBAL_ID;

    typedef std::shared_ptr<MapEntity> Ptr;

    MapPosition::Ptr &getPosition() {
        return position;
    }

    void setPosition(MapPosition::Ptr nextPos) {
        position = std::move(nextPos);
    }

    int getId() {
        return id;
    }

    std::string getUId() {
        return std::to_string(id);
    }
protected:
    MapPosition::Ptr position;

    MapEntity() : position(nullptr), id(GLOBAL_ID++) {}
private:
    int id;
};

#endif //HIVEMIND_MAPENTITY_H
