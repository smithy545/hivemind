//
// Created by philip on 1/23/20.
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

    MapNode(int x, int y);

    MapNode(int x, int y, bool passable);

    MapNode(int x, int y, bool passable, int type);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    bool isPassable() const;

    void setPassable(bool val);

    std::unordered_set<Ptr> &getNeighbors();

    int getType() const;

    void setType(int type);
private:
    int x;
    int y;
    int type;
    bool passable;
    std::unordered_set<Ptr> neighbors;
};

#endif //SOCIETY_MAPNODE_H
