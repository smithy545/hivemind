//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_MAPNODE_H
#define HIVEMIND_MAPNODE_H

#include <memory>
#include <deque>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>


class MapEntity;

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

    std::unordered_map<std::string, std::shared_ptr<MapEntity>> &getEntities() {
        return entities;
    }

    void setEntities(const std::unordered_map<std::string, std::shared_ptr<MapEntity>> &entities) {
        this->entities = entities;
    }

    void addEntity(const std::string &id, std::shared_ptr<MapEntity> entity) {
        entities[id] = std::move(entity);
    }

    void removeEntity(const std::string &id) {
        entities.erase(id);
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
    std::unordered_map<std::string, std::shared_ptr<MapEntity>> entities;
};

#endif //HIVEMIND_MAPNODE_H
