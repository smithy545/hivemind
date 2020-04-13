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

    // topology
    const std::vector<MapNode::Ptr> &getNodes() override;

    MapNode::Ptr getNode(int x, int y) override;

    std::vector<MapNode::Ptr> getNeighbors(MapNode::Ptr node) override;

    //TODO
    void addPerson();

private:
    std::vector<GridMap::Ptr> subMaps;
};


#endif //SOCIETY_WORLDMAP_H
