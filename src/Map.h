//
// Created by philip on 1/26/20.
//

#ifndef HIVEMIND_MAP_H
#define HIVEMIND_MAP_H

#include <iterator>
#include <memory>
#include <vector>
#include <vector>

#include "MapActor.h"
#include "MapNode.h"
#include "Mesh.h"


class Map {
public:
    typedef std::shared_ptr<Map> Ptr;

    virtual const std::vector<MapActor::Ptr> &getActors() = 0;
    virtual const std::vector<MapNode::Ptr> &getNodes() = 0;
    virtual MapNode::Ptr getNode(int x, int y) = 0;

    virtual void addActor(MapActor::Ptr actor, int x, int y) = 0;
    virtual bool moveActor(std::weak_ptr<MapActor> actor, MapNode::Ptr nextPos) = 0;

    virtual Mesh::Ptr generateMesh(float screenWidth, float screenHeight, float tileSize) = 0;
};

#endif //HIVEMIND_MAP_H