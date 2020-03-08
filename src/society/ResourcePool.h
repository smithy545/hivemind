//
// Created by Philip on 3/3/2020.
//

#ifndef SOCIETY_RESOURCEPOOL_H
#define SOCIETY_RESOURCEPOOL_H

#include <memory>
#include <type_traits>
#include <vector>

#include "pathing/MapNode.h"
#include "world/Prop.h"
#include "world/Structure.h"

#include "ProductionRole.h"


// A collection of locations and economic relations that move given inputs to given storage locations
template<class Resource>
class ResourcePool {
public:
    typedef std::shared_ptr<ResourcePool> Ptr;

    ResourcePool() {
        static_assert(std::is_base_of_v<Prop, Resource>, "Resource is not derived from Prop");
    }

    void store(int count);

    std::shared_ptr<Resource> withdraw(int count);

private:
    // places available for storing goods
    std::vector<MapNode::Ptr> storageNodes;
    std::vector<Structure::Ptr> storageStructures;
};


#endif //SOCIETY_RESOURCEPOOL_H
