//
// Created by Philip on 2/25/2020.
//

#ifndef HIVEMIND_USERINTERFACE_H
#define HIVEMIND_USERINTERFACE_H

#include <memory>

#include "src/render/Mesh.h"


class UserInterface {
public:
    typedef std::shared_ptr<UserInterface> Ptr;

    Mesh::Ptr generateMesh(float screenWidth, float screenHeight, float tileSize);
};


#endif //HIVEMIND_USERINTERFACE_H