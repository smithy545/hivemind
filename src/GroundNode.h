//
// Created by Philip on 2/23/2020.
//

#ifndef HIVEMIND_GROUNDNODE_H
#define HIVEMIND_GROUNDNODE_H

#include "MapNode.h"


class GroundNode : public MapNode {
public:
    enum GroundType {
        SOIL,
        TILLED_SOIL,
        PLANT,
        ROAD
    };

    GroundNode(int x, int y) : GroundNode(x, y, SOIL) {}
    GroundNode(int x, int y, GroundType type) : MapNode(x, y), type(type) {}

    GroundType type;
};


#endif //HIVEMIND_GROUNDNODE_H
