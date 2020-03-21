//
// Created by Philip on 3/21/2020.
//


#include "WorldEntity.h"

MapNode::Ptr &WorldEntity::getPosition() {
    return position;
}

void WorldEntity::setPosition(MapNode::Ptr node) {
    position = std::move(node);
}

glm::mat4 WorldEntity::getModel(int tileSize) {
    return glm::translate(glm::mat4(1), glm::vec3(getX(tileSize), getY(tileSize), 0));
}

int WorldEntity::getX(int tileSize) {
    if (position == nullptr)
        return -1;
    return position->getX() * tileSize;
}

int WorldEntity::getY(int tileSize) {
    if (position == nullptr)
        return -1;
    return position->getY() * tileSize;
}

int WorldEntity::getX() {
    if (position == nullptr)
        return -1;
    return position->getX();
}

int WorldEntity::getY() {
    if (position == nullptr)
        return -1;
    return position->getY();
}

int WorldEntity::getWidth() {
    return 1;
}

int WorldEntity::getHeight() {
    return 1;
}

unsigned int WorldEntity::getId() {
    return id;
}

std::string WorldEntity::getIdString() {
    return std::to_string(id);
}

const std::string &WorldEntity::getSpriteName() const {
    return spriteName;
}

void WorldEntity::setSpriteName(const std::string &spriteName) {
    this->spriteName = spriteName;
}

json WorldEntity::pack() {
    return json::parse(fmt::format(
            R"({{"sprite":"{0}","x":{1},"y":{2}}})",
            getSpriteName(),
            getX(),
            getY()
    ));
}

bool WorldEntity::unpack(json data) {
    if (validate(data)) {
        spriteName = data["spriteName"];
        return true;
    }
    return false;
}