//
// Created by Philip on 2/25/2020.
//

#ifndef SOCIETY_INTERFACE_H
#define SOCIETY_INTERFACE_H

#include <string>
#include <vector>

#include "interface/InterfaceNode.h"
#include "macros.h"
#include "Scene.h"
#include "State.h"
#include "world/God.h"


class Interface {
public:
    POINTERIZE(Interface);

    void update(const State::Ptr &state, Scene::Ptr &scene, God::Ptr &god);
};


#endif //SOCIETY_INTERFACE_H
