//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_UIENTITY_H
#define SOCIETY_UIENTITY_H

#include <memory>

#include "common/Entity.h"


class UIEntity : public Entity {
public:
    typedef std::shared_ptr<UIEntity> Ptr;

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
