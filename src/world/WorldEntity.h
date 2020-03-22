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

#include "pathing/MapNode.h"


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

    int getX() {
        if (position == nullptr)
            return 0;
        return position->getX();
    }

    int getY() {
        if (position == nullptr)
            return 0;
        return position->getY();
    }

    int getWidth() {
        return 1;
    }

    int getHeight() {
        return 1;
    }

    unsigned int getId() {
        return id;
    }

    std::string getIdString() {
        return std::to_string(id);
    }

    const std::string &getSpriteName() const;

    void setSpriteName(const std::string &spriteName);

protected:
    MapNode::Ptr position;
    std::string spriteName;

    explicit WorldEntity(std::string spriteName) : WorldEntity(std::move(spriteName), nullptr) {}

    WorldEntity(std::string spriteName, MapNode::Ptr initialLocation) : position(std::move(initialLocation)),
                                                                        spriteName(std::move(spriteName)),
                                                                        id(GLOBAL_ID++) {}

private:
    unsigned int id;
};

#endif //SOCIETY_WORLDENTITY_H
