//
// Created by Philip on 2/25/2020.
//

#ifndef SOCIETY_INTERFACE_H
#define SOCIETY_INTERFACE_H

#include <string>
#include <vector>

#include "macros.h"
#include "render/Camera.h"
#include "State.h"
#include "world/God.h"


class Interface {
public:
    POINTERIZE(Interface);

    explicit Interface(God::Ptr god);

    void update(const State::Ptr &state, Camera::Ptr &camera, God::Ptr &god);
};


#endif //SOCIETY_INTERFACE_H
