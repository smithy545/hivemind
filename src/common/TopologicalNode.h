//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_TOPOLOGICALNODE_H
#define SOCIETY_TOPOLOGICALNODE_H

#include <memory>
#include <vector>


class TopologicalNode {
public:
    typedef std::shared_ptr<TopologicalNode> Ptr;

    virtual std::vector<Ptr> &getNeighbors() = 0;
};

#endif //SOCIETY_TOPOLOGICALNODE_H
