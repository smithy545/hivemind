//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_SCENE_H
#define SOCIETY_SCENE_H

#include <vector>

#include "common/Body.h"
#include "macros.h"
#include "render/Camera.h"
#include "render/Mesh.h"
#include "render/RenderNode.h"


class Scene {
public:
    POINTERIZE(Scene);

    Scene(int width, int height);

    void add_to_scene(const std::string& shader_name, Mesh::Ptr mesh, const Body::Ptr& body);

    void cleanup();

    _MVAR_GETSET(Camera::Ptr, camera, public, private);
    _MVAR_GETSET(RenderNode::Ptr, render_head, public, private);
};


#endif //SOCIETY_SCENE_H
