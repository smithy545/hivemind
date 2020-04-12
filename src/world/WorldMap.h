//
// Created by smith on 4/9/2020.
//

#ifndef SOCIETY_WORLDMAP_H
#define SOCIETY_WORLDMAP_H

#include <memory>
#include <pathing/Map.h>
#include <pathing/MapNode.h>
#include <pathing/GridMap.h>
#include <string>


class WorldMap : public Map {
public:
    typedef std::shared_ptr<WorldMap> Ptr;

    WorldMap();

    explicit WorldMap(const std::string &mapFile);

    // topology
    const std::vector<MapNode::Ptr> &getNodes() override;

    MapNode::Ptr getNode(int x, int y) override;

    //TODO
    void expandNorth();

    void expandWest();

    void expandSouth();

    void expandEast();

private:
    std::vector<GridMap::Ptr> subMaps;
};


#endif //SOCIETY_WORLDMAP_H
