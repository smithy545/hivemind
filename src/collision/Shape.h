//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_SHAPE_H
#define SOCIETY_SHAPE_H

#include "macros.h"

class Shape {
public:
    POINTERIZE(Shape);

    virtual bool collides(Ptr other) = 0;
};


#endif //SOCIETY_SHAPE_H
