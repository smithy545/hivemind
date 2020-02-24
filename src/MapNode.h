//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_MAPNODE_H
#define HIVEMIND_MAPNODE_H

#include <memory>
#include <deque>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class MapEntity;

class MapNode {
public:
    typedef std::shared_ptr<MapNode> Ptr;
    typedef std::deque<Ptr> MapPath;

    MapNode(int x, int y) : MapNode(x, y, true) {}

    MapNode(int x, int y, bool passable) : x(x), y(y), passable(passable) {}

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

    std::vector<Ptr> &getNeighbors() {
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

private:
    int x;
    int y;
    bool passable;
    std::vector<Ptr> neighbors;
    std::unordered_map<std::string, std::shared_ptr<MapEntity>> entities;
};

#endif //HIVEMIND_MAPNODE_H
