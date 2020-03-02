//
// Created by Philip on 2/9/2020.
//

#ifndef HIVEMIND_WORLDENTITY_H
#define HIVEMIND_WORLDENTITY_H

#include <memory>
#include <string>
#include <utility>

#include "src/pathing/MapNode.h"


class WorldEntity {
public:
    static unsigned int GLOBAL_ID;

    typedef std::shared_ptr<WorldEntity> Ptr;

    MapNode::Ptr &getPosition() {
        return position;
    }

    void setPosition(MapNode::Ptr node) {
        position = std::move(node);
    }

    unsigned int getId() {
        return id;
    }

    std::string getIdString() {
        return std::to_string(id);
    }

protected:
    MapNode::Ptr position;

    WorldEntity() : WorldEntity(nullptr) {}

    explicit WorldEntity(MapNode::Ptr initialLocation) : position(std::move(initialLocation)),
                                                         id(GLOBAL_ID++) {}

private:
    unsigned int id;
};

#endif //HIVEMIND_WORLDENTITY_H
