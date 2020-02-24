//
// Created by philip on 1/23/20.
//

#include "Pather.h"

#include <cmath>
#include <unordered_map>


MapNode::MapPath Pather::genAStarPath(const MapNode::Ptr &start, const MapNode::Ptr &end) {
    MapNode::MapPath path;

    std::unordered_map<std::string, PathNode::Ptr> open;
    std::unordered_map<std::string, PathNode::Ptr> closed;

    open[genKey(start)] = std::make_shared<PathNode>(start, 0, 0, nullptr);
    while(!open.empty()) {
        std::string minKey;
        for(std::pair<std::string, PathNode::Ptr> el: open) {
            if(minKey.empty() || el.second->getF() < open[minKey]->getF()) {
                minKey = genKey(el.second->position);
            }
        }

        PathNode::Ptr parent = open[minKey];
        open.erase(minKey);
        for(const MapNode::Ptr &neighbor: parent->position->neighbors) {
            std::string key = genKey(neighbor);
            if(closed.count(key) > 0)
                continue;
            if(end->x == neighbor->x && end->y == neighbor->y) {
                path.push_front(end);
                while(parent->previous != nullptr) {
                    path.push_front(parent->position);
                    parent = parent->previous;
                }
                return path;
            } else if(neighbor->passable) {
                double g = parent->g + distanceEuclid(neighbor, parent->position);
                double h = distanceEuclid(neighbor, end);

                if(open.count(key) > 0) {
                    if(open[key]->getF() < g + h) {
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

std::string Pather::genKey(const MapNode::Ptr &pos) {
    return std::to_string(pos->x) + ":" + std::to_string(pos->y);
}

double Pather::distanceEuclid(const MapNode::Ptr &a, const MapNode::Ptr &b) {
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    return std::sqrt(dx*dx + dy*dy);
}