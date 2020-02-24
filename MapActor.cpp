//
// Created by Philip on 2/23/2020.
//


#include "MapActor.h"


void MapActor::addToPath(const MapNode::Ptr& nextPos) {
    path.push_back(nextPos);
}