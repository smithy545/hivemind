//
// Created by philip on 1/23/20.
//

#include "Pather.h"

#include <cmath>
#include <unordered_map>


MapNode::MapPath Pather::genAStarPath(const TopologicalMapNode::Ptr &start, const TopologicalMapNode::Ptr &end) {
    MapNode::MapPath path;

    std::unordered_map<std::string, PathNode::Ptr> open;
    std::unordered_map<std::string, PathNode::Ptr> closed;

    open[genKey(start)] = std::make_shared<PathNode>(start, 0, 0, nullptr);
    while (!open.empty()) {
        std::string minKey;
        for (const auto &el: open) {
            if (minKey.empty() || el.second->getF() < open[minKey]->getF()) {
                minKey = genKey(el.second->position);
            }
        }

        PathNode::Ptr parent = open[minKey];
        open.erase(minKey);
        for (const auto &neighborPtr: std::dynamic_pointer_cast<TopologicalMapNode>(parent->position)->getNeighbors()) {
            auto neighbor = std::dynamic_pointer_cast<TopologicalMapNode>(neighborPtr);
            std::string key = genKey(neighbor);
            if (closed.count(key) > 0)
                continue;
            if (end->getX() == neighbor->getX() && end->getY() == neighbor->getY()) {
                path.push_front(end);
                while (parent->previous != nullptr) {
                    path.push_front(parent->position);
                    parent = parent->previous;
                }
                return path;
            } else if (neighbor->isPassable()) {
                double g = parent->g + distanceEuclid(neighbor, parent->position);
                double h = distanceEuclid(neighbor, end);

                if (open.count(key) > 0) {
                    if (open[key]->getF() < g + h) {
                        continue;
                    } else {
                        open[key]->previous = parent;
                    }
                } else {
                    open[key] = std::make_shared<PathNode>(neighbor, g, h, parent);
                }
            }
        }
        closed[minKey] = parent;
    }

    return path;
}

MapNode::MapPath Pather::genAStarPath(const Map::Ptr &map, const MapNode::Ptr &start, const MapNode::Ptr &end) {
    MapNode::MapPath path;

    std::unordered_map<std::string, PathNode::Ptr> open;
    std::unordered_map<std::string, PathNode::Ptr> closed;

    open[genKey(start)] = std::make_shared<PathNode>(start, 0, 0, nullptr);
    while (!open.empty()) {
        std::string minKey;
        for (const auto &el: open) {
            if (minKey.empty() || el.second->getF() < open[minKey]->getF()) {
                minKey = genKey(el.second->position);
            }
        }

        PathNode::Ptr parent = open[minKey];
        open.erase(minKey);
        for (const auto &neighbor: map->getNeighbors(parent->position)) {
            std::string key = genKey(neighbor);
            if (closed.count(key) > 0)
                continue;
            if (end->getX() == neighbor->getX() && end->getY() == neighbor->getY()) {
                path.push_front(end);
                while (parent->previous != nullptr) {
                    path.push_front(parent->position);
                    parent = parent->previous;
                }
                return path;
            } else if (neighbor->isPassable()) {
                double g = parent->g + distanceEuclid(neighbor, parent->position);
                double h = distanceEuclid(neighbor, end);

                if (open.count(key) > 0) {
                    if (open[key]->getF() < g + h) {
                        continue;
                    } else {
                        open[key]->previous = parent;
                    }
                } else {
                    open[key] = std::make_shared<PathNode>(neighbor, g, h, parent);
                }
            }
        }
        closed[minKey] = parent;
    }

    return path;
};

std::string Pather::genKey(const MapNode::Ptr &pos) {
    return std::to_string(pos->getX()) + ":" + std::to_string(pos->getY());
}

double Pather::distanceEuclid(const MapNode::Ptr &a, const MapNode::Ptr &b) {
    double dx = a->getX() - b->getX();
    double dy = a->getY() - b->getY();
    return std::sqrt(dx * dx + dy * dy);
}