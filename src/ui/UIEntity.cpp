//
// Created by Philip on 3/7/2020.
//

#include "UIEntity.h"
#include <glm/ext.hpp>

UIEntity::UIEntity(int x, int y, int width, int height) : Entity(R"({"type":"object"})"_json),
                                                          x(x), y(y), width(width), height(height) {}

json UIEntity::pack() {
    return {
            {"x",      x},
            {"y",      y},
            {"width",  width},
            {"height", height}
    };
}

bool UIEntity::unpack(json data) {
    return false;
}

glm::mat4 UIEntity::getModel() {
    return glm::translate(glm::mat4(1), glm::vec3(getX(), getY(), 0));
}

int UIEntity::getX() {
    return x;
}

int UIEntity::getY() {
    return y;
}

int UIEntity::getWidth() {
    return width;
}

int UIEntity::getHeight() {
    return height;
}

bool UIEntity::resize(int width, int height) {
    this->width = width;
    this->height = height;

    return true;
}

const std::string &UIEntity::getSpriteName() const {
    return spriteName;
}
