//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_TOPOLOGICALNODE_H
#define SOCIETY_TOPOLOGICALNODE_H

#include <vector>

#include "macros.h"


class TopologicalNode {
public:
    POINTERIZE(TopologicalNode)

    virtual std::vector<Ptr> &getNeighbors() = 0;
};

#endif //SOCIETY_TOPOLOGICALNODE_H
