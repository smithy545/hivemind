//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_UIENTITY_H
#define SOCIETY_UIENTITY_H

#include "common/Entity.h"


class UIEntity : public Entity {
public:
    int getX() override;

    int getY() override;

    int getWidth() override;

    int getHeight() override;

    bool resize(int width, int height);

private:
    int x{};
    int y{};
    int width{};
    int height{};
};


#endif //SOCIETY_UIENTITY_H
