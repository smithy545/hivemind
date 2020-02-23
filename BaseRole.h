//
// Created by Philip on 2/23/2020.
//

#ifndef HIVEMIND_BASEROLE_H
#define HIVEMIND_BASEROLE_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "MapNode.h"


class BaseRole {
public:
    virtual MapNode::Ptr getTaskDestination(std::string taskName) = 0;
    virtual std::vector<std::string> getAvailableTasks() = 0;

    const std::string &getName() const {
        return name;
    }

protected:
    std::string name;

    explicit BaseRole(std::string name) : name(std::move(name)) {}
};


#endif //HIVEMIND_BASEROLE_H
