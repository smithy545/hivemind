//
// Created by philip on 1/23/20.
//

#ifndef SOCIETY_GRIDNODE_H
#define SOCIETY_GRIDNODE_H

#include <deque>
#include <memory>
#include <unordered_set>

#include "MapNode.h"


class GridNode : public MapNode {
public:
    typedef std::shared_ptr<GridNode> Ptr;
    typedef std::deque<Ptr> MapPath;

    GridNode(int x, int y);

    GridNode(int x, int y, bool passable);

    GridNode(int x, int y, bool passable, int type);

    int getX() override;

    void setX(int x);

    int getY() override;

    void setY(int y);

    bool isPassable() override;

    void setPassable(bool val);

    std::unordered_set<MapNode::Ptr> &getNeighbors() override;

    int getType() const;

    void setType(int type);

private:
    int x;
    int y;
    int type;
    bool passable;
    std::unordered_set<Ptr> neighbors;
};

#endif //SOCIETY_GRIDNODE_H
