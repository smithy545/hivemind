//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_UIENTITY_H
#define SOCIETY_UIENTITY_H

#include <memory>


class UIEntity {
public:
    typedef std::shared_ptr<UIEntity> Ptr;

    int getX();

    int getY();

    int getWidth();

    int getHeight();

    bool resize(int width, int height);

private:
    int x{};
    int y{};
    int width{};
    int height{};
};


#endif //SOCIETY_UIENTITY_H
