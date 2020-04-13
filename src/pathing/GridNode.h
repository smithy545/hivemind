//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_GRIDNODE_H
#define SOCIETY_GRIDNODE_H

#include <memory>

#include "MapNode.h"


class GridNode : public MapNode {
public:
    typedef std::shared_ptr<GridNode> Ptr;

    GridNode(int x, int y);

    GridNode(int x, int y, bool passable);

    int getX();

    int getY();

    bool isPassable();

private:
    int x, y;
    bool passable;
};


#endif //SOCIETY_GRIDNODE_H
