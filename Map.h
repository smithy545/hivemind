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


class Map {
public:
    typedef std::shared_ptr<Map> Ptr;
    typedef std::iterator<std::input_iterator_tag, MapNode::Ptr> MapStream;

    virtual std::vector<MapActor::Ptr> getActors() = 0;
    virtual std::vector<MapNode::Ptr> getNodes() = 0;
    virtual MapNode::Ptr getNode(int x, int y) = 0;
};

#endif //HIVEMIND_MAP_H
