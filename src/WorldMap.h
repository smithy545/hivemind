//
// Created by smith on 4/9/2020.
//

#ifndef SOCIETY_WORLDMAP_H
#define SOCIETY_WORLDMAP_H

#include <memory>
#include <pathing/Map.h>
#include <pathing/GridNode.h>
#include <pathing/GridMap.h>
#include <string>
#include <vector>


class WorldMap : public Map {
public:
    typedef std::shared_ptr<WorldMap> Ptr;

    WorldMap();

    WorldMap(int xOffset, int yOffset);

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


#endif //SOCIETY_WORLDMAP_H
