//
// Created by Philip on 3/3/2020.
//

#ifndef SOCIETY_RESOURCEPOOL_H
#define SOCIETY_RESOURCEPOOL_H

#include <memory>
#include <vector>

#include "pathing/MapNode.h"
#include "world/Prop.h"

#include "ProductionRole.h"


// A collection of locations and economic relations that move given inputs to given storage locations
class ResourcePool {
public:
    typedef std::shared_ptr<ResourcePool> Ptr;
private:
    // places available for storing goods
    std::vector<MapNode::Ptr> storage;
    std::vector<Prop::Ptr> storableProps;
    std::vector<ProductionRole::Ptr> producers;
};


#endif //SOCIETY_RESOURCEPOOL_H
