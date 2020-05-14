//
// Created by smith on 4/9/2020.
//

#ifndef SOCIETY_WORLD_H
#define SOCIETY_WORLD_H

#include <memory>
#include <string>
#include <vector>

#include "pathing/Map.h"
#include "pathing/GridNode.h"
#include "pathing/GridMap.h"


class World : public Map {
public:
    typedef std::shared_ptr<World> Ptr;

    World();

    World(int xOffset, int yOffset);

    // topology
    const std::vector<MapNode::Ptr> &getNodes() override;

    MapNode::Ptr getNode(int x, int y) override;

    std::vector<MapNode::Ptr> getNeighbors(MapNode::Ptr node) override;

private:
    static const int MAX_SUBMAP_X{64};
    static const int MAX_SUBMAP_Y{64};
    const int subMapSize{100};
    int width{0};
    int height{0};
    GridMap::Ptr subMaps[MAX_SUBMAP_Y][MAX_SUBMAP_X];
};


#endif //SOCIETY_WORLD_H
