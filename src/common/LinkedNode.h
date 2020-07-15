//
// Created by Philip on 5/13/2020.
//

#ifndef SOCIETY_LINKEDNODE_H
#define SOCIETY_LINKEDNODE_H

#include "macros.h"


class LinkedNode {
public:
    PTR(LinkedNode);

    virtual Ptr get_next() = 0;
};


#endif //SOCIETY_LINKEDNODE_H
