//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_MAPNODE_H
#define SOCIETY_MAPNODE_H

#include <deque>
#include <memory>
#include <unordered_set>


class MapNode {
public:
    typedef std::shared_ptr<MapNode> Ptr;
    typedef std::deque<Ptr> MapPath;

    virtual int getX() = 0;

    virtual int getY() = 0;

    virtual bool isPassable() = 0;

    virtual std::unordered_set<Ptr> &getNeighbors() = 0;
};

#endif //SOCIETY_MAPNODE_H
