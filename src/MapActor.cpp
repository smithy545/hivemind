//
// Created by Philip on 2/23/2020.
//


#include "MapActor.h"


void MapActor::addToPath(MapNode::Ptr nextPos) {
    path.push_front(std::move(nextPos));
}
