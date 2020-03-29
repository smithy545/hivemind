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

    enum Type {
        GROUND,
        NATURE,
        ROAD,
        STRUCTURE
    };

    MapNode(int x, int y);

    MapNode(int x, int y, bool passable);

    MapNode(int x, int y, bool passable, Type type);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    bool isPassable() const;

    void setPassable(bool val);

    std::unordered_set<Ptr> &getNeighbors();

    Type getType() const;

    void setType(Type type);
private:
    int x;
    int y;
    Type type;
    bool passable;
    std::unordered_set<Ptr> neighbors;
};

#endif //SOCIETY_MAPNODE_H
