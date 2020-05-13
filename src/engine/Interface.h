//
// Created by Philip on 2/25/2020.
//

#ifndef SOCIETY_INTERFACE_H
#define SOCIETY_INTERFACE_H

#include <memory>
#include <string>
#include <ui/UINode.h>
#include <vector>

#include "State.h"


class Interface {
public:
    typedef std::shared_ptr<Interface> Ptr;

    explicit Interface(const std::string &configPath);

    void update(const State::Ptr &state);
private:
    std::vector<UINode::Ptr> nodes;
};


#endif //SOCIETY_INTERFACE_H
