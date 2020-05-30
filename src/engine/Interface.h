//
// Created by Philip on 2/25/2020.
//

#ifndef SOCIETY_INTERFACE_H
#define SOCIETY_INTERFACE_H

#include <memory>
#include <string>
#include <vector>

#include "interface/InterfaceNode.h"
#include "State.h"


class Interface {
public:
    typedef std::shared_ptr<Interface> Ptr;

    Interface();

    void update(const State::Ptr &state);
private:
    std::vector<InterfaceNode::Ptr> nodes;
};


#endif //SOCIETY_INTERFACE_H
