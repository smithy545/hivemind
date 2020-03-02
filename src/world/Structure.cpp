//
// Created by Philip on 2/12/2020.
//

#include "Structure.h"


Structure::Structure(const MapNode::Ptr &node) : WorldActor(node) {

}

WorldActor::Action Structure::update(std::shared_ptr<GridMap> map) {
    return IDLE;
}