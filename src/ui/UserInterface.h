//
// Created by Philip on 2/25/2020.
//

#ifndef HIVEMIND_USERINTERFACE_H
#define HIVEMIND_USERINTERFACE_H

#include <memory>

#include "src/render/Mesh.h"
#include "src/render/Renderer.h"
#include "src/world/GridMap.h"


class UserInterface {
public:
    typedef std::shared_ptr<UserInterface> Ptr;

    explicit UserInterface(GridMap::Ptr map);

    void update(const bool keys[256], float mouseX, float mouseY, float mouseScroll, const Renderer::Ptr &renderer);

private:
    GridMap::Ptr map;

};


#endif //HIVEMIND_USERINTERFACE_H
