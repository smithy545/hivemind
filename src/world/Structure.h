//
// Created by Philip on 2/12/2020.
//

#ifndef SOCIETY_STRUCTURE_H
#define SOCIETY_STRUCTURE_H

#include <memory>

#include "pathing/MapNode.h"

#include "WorldActor.h"


class GridMap;

class Structure : public WorldActor {
public:
    typedef std::shared_ptr<Structure> Ptr;

    explicit Structure(const MapNode::Ptr &node);

    Action update(std::shared_ptr<GridMap> map) override;
};


#endif //SOCIETY_STRUCTURE_H
