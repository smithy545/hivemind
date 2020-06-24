//
// Created by Philip on 2/25/2020.
//

#ifndef SOCIETY_INTERFACE_H
#define SOCIETY_INTERFACE_H

#include <string>
#include <vector>

#include "interface/InterfaceNode.h"
#include "macros.h"
#include "State.h"


class Interface {
public:
    POINTERIZE(Interface);

    void update(const State::Ptr &state);
};


#endif //SOCIETY_INTERFACE_H
