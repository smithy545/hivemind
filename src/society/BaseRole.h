//
// Created by Philip on 2/23/2020.
//

#ifndef HIVEMIND_BASEROLE_H
#define HIVEMIND_BASEROLE_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "pathing/MapNode.h"
#include "world/WorldEntity.h"


class BaseRole {
public:
    typedef std::shared_ptr<BaseRole> Ptr;

    virtual std::string getNextTask(std::string currentTask) = 0;

    virtual MapNode::Ptr getTaskDestination(std::string taskName) = 0;

    virtual std::vector<std::string> getAvailableTasks() = 0;

    const std::string &getName() const {
        return name;
    }

protected:
    explicit BaseRole(std::string name) : name(std::move(name)) {}

private:
    std::string name;
};


#endif //HIVEMIND_BASEROLE_H
