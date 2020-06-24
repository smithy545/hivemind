//
// Created by philip on 1/23/20.
//

#include "Pather.h"

#include <cmath>
#include <unordered_map>


MapNode::MapPath Pather::get_astar_path(const TopologicalMapNode::Ptr &start, const TopologicalMapNode::Ptr &end) {
    MapNode::MapPath path;

    std::unordered_map<std::string, PathNode::Ptr> open;
    std::unordered_map<std::string, PathNode::Ptr> closed;

    open[get_node_key(start)] = std::make_shared<PathNode>(start, 0, 0, nullptr);
    while (!open.empty()) {
        std::string minKey;
        for (const auto &el: open) {
            if (minKey.empty() || el.second->get_f() < open[minKey]->get_f()) {
                minKey = get_node_key(el.second->position);
            }
        }

        PathNode::Ptr parent = open[minKey];
        open.erase(minKey);
        for (const auto &neighborPtr: std::dynamic_pointer_cast<TopologicalMapNode>(parent->position)->get_neighbors()) {
            auto neighbor = std::dynamic_pointer_cast<TopologicalMapNode>(neighborPtr);
            std::string key = get_node_key(neighbor);
            if (closed.count(key) > 0)
                continue;
            if (end->get_x() == neighbor->get_x() && end->get_y() == neighbor->get_y()) {
                path.push_front(end);
                while (parent->previous != nullptr) {
                    path.push_front(parent->position);
                    parent = parent->previous;
                }
                return path;
            } else if (neighbor->is_passable()) {
                double g = parent->g + distance_euclid(neighbor, parent->position);
                double h = distance_euclid(neighbor, end);

                if (open.count(key) > 0) {
                    if (open[key]->get_f() < g + h) {
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

MapNode::MapPath Pather::get_astar_path(const Map::Ptr &map, const MapNode::Ptr &start, const MapNode::Ptr &end) {
    MapNode::MapPath path;

    std::unordered_map<std::string, PathNode::Ptr> open;
    std::unordered_map<std::string, PathNode::Ptr> closed;

    open[get_node_key(start)] = std::make_shared<PathNode>(start, 0, 0, nullptr);
    while (!open.empty()) {
        std::string minKey;
        for (const auto &el: open) {
            if (minKey.empty() || el.second->get_f() < open[minKey]->get_f()) {
                minKey = get_node_key(el.second->position);
            }
        }

        PathNode::Ptr parent = open[minKey];
        open.erase(minKey);
        for (const auto &neighbor: map->get_neighbors(parent->position)) {
            std::string key = get_node_key(neighbor);
            if (closed.count(key) > 0)
                continue;
            if (end->get_x() == neighbor->get_x() && end->get_y() == neighbor->get_y()) {
                path.push_front(end);
                while (parent->previous != nullptr) {
                    path.push_front(parent->position);
                    parent = parent->previous;
                }
                return path;
            } else if (neighbor->is_passable()) {
                double g = parent->g + distance_euclid(neighbor, parent->position);
                double h = distance_euclid(neighbor, end);

                if (open.count(key) > 0) {
                    if (open[key]->get_f() < g + h) {
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

std::string Pather::get_node_key(const MapNode::Ptr &pos) {
    return std::to_string(pos->get_x()) + ":" + std::to_string(pos->get_y());
}

double Pather::distance_euclid(const MapNode::Ptr &a, const MapNode::Ptr &b) {
    double dx = a->get_x() - b->get_x();
    double dy = a->get_y() - b->get_y();
    return std::sqrt(dx * dx + dy * dy);
}