//
// Created by Philip on 2/9/2020.
//

#ifndef SOCIETY_WORLDENTITY_H
#define SOCIETY_WORLDENTITY_H

#include <memory>
#include <string>
#include <utility>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "common/Entity.h"
#include "pathing/MapNode.h"


class WorldEntity : public Entity {
public:
    static unsigned int GLOBAL_ID;

    typedef std::shared_ptr<WorldEntity> Ptr;

    MapNode::Ptr &getPosition() {
        return position;
    }

    void setPosition(MapNode::Ptr node) {
        position = std::move(node);
    }

    glm::mat4 getModel(int tileSize) {
        return glm::translate(glm::mat4(1), glm::vec3(getX(tileSize), getY(tileSize), 0));
    }

    int getX(int tileSize) {
        if (position == nullptr)
            return 0;
        return position->getX() * tileSize;
    }

    int getY(int tileSize) {
        if (position == nullptr)
            return 0;
        return position->getY() * tileSize;
    }

    int getX() override {
        if (position == nullptr)
            return 0;
        return position->getX();
    }

    int getY() override {
        if (position == nullptr)
            return 0;
        return position->getY();
    }

    int getWidth() override {
        return 1;
    }

    int getHeight() override {
        return 1;
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

#endif //SOCIETY_WORLDENTITY_H
