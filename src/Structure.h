//
// Created by Philip on 2/12/2020.
//

#ifndef HIVEMIND_STRUCTURE_H
#define HIVEMIND_STRUCTURE_H


#include <memory>

#include "MapActor.h"
#include "MapNode.h"

class GridMap;


class Structure : public MapActor {
public:
    typedef std::shared_ptr<Structure> Ptr;

    explicit Structure(const MapNode::Ptr &node);

    Action update(std::shared_ptr<GridMap> map) override;
};


#endif //HIVEMIND_STRUCTURE_H
