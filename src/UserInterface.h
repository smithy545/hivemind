//
// Created by Philip on 2/25/2020.
//

#ifndef HIVEMIND_USERINTERFACE_H
#define HIVEMIND_USERINTERFACE_H

#include <memory>

#include "Renderable.h"


class UserInterface : public Renderable {
public:
    typedef std::shared_ptr<UserInterface> Ptr;

    Mesh::Ptr generateMesh(float screenWidth, float screenHeight, float tileSize) override;
};


#endif //HIVEMIND_USERINTERFACE_H
