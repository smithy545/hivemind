//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_BOUND_H
#define SOCIETY_BOUND_H

#include "macros.h"

class Bound {
public:
    PTR(Bound);

    virtual bool collides(Ptr other) = 0;
};


#endif //SOCIETY_BOUND_H
