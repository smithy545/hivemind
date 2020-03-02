//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_MAPNODE_H
#define HIVEMIND_MAPNODE_H

#include <memory>
#include <deque>
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
    };;

    MapNode(int x, int y) : MapNode(x, y, true) {}

    MapNode(int x, int y, bool passable) : MapNode(x, y, passable, GROUND) {}

    MapNode(int x, int y, bool passable, Type type) : x(x), y(y), passable(passable), type(type) {}

    int getX() const {
        return x;
    }

    void setX(int x) {
        this->x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        this->y = y;
    }

    bool isPassable() const {
        return passable;
    }

    void setPassable(bool val) {
        passable = val;
    }

    std::unordered_set<Ptr> &getNeighbors() {
        return neighbors;
    }

    Type getType() const {
        return type;
    }

    void setType(Type type) {
        MapNode::type = type;
    }

private:
    int x;
    int y;
    Type type;
    bool passable;
    std::unordered_set<Ptr> neighbors;
};

#endif //HIVEMIND_MAPNODE_H
