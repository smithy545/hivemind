//
// Created by Philip on 2/9/2020.
//

#ifndef HIVEMIND_MAPENTITY_H
#define HIVEMIND_MAPENTITY_H

#include <memory>
#include <string>
#include <utility>

#include "src/pathing/MapPosition.h"


class MapEntity {
public:
    static int GLOBAL_ID;

    typedef std::shared_ptr<MapEntity> Ptr;

    MapPosition::Ptr &getPosition() {
        return position;
    }

    MapNode::Ptr getMapNode() {
        return position->getNode();
    }

    void setMapNode(const MapNode::Ptr &nextPos) {
        position->setNode(nextPos);
    }

    int getId() {
        return id;
    }

    std::string getUId() {
        return std::to_string(id);
    }

protected:
    MapPosition::Ptr position;

    MapEntity() : MapEntity(nullptr) {}

    explicit MapEntity(const MapNode::Ptr &initialLocation) : position(std::make_shared<MapPosition>(initialLocation)),
                                                              id(GLOBAL_ID++) {}

private:
    int id;
};

#endif //HIVEMIND_MAPENTITY_H
