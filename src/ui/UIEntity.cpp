//
// Created by Philip on 3/7/2020.
//

#include "UIEntity.h"

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
