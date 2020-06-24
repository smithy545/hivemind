//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_SCENE_H
#define SOCIETY_SCENE_H

#include <vector>

#include "collision/CollisionNode.h"
#include "macros.h"
#include "render/Camera.h"
#include "render/Mesh.h"
#include "render/RenderNode.h"


class Scene {
public:
    POINTERIZE(Scene);

    Scene(int width, int height);

    void add_to_scene(const std::string& shader_name, Mesh::Ptr mesh, const Body::Ptr& body, bool physics = false);

    void cleanup();

    CollisionNode::Ptr get_collision_tree();

    _MVAR_GETSET(camera, Camera::Ptr, public, private)
    _MVAR_GETSET(render_head, RenderNode::Ptr, public, private)
private:
    CollisionNode::Ptr collision_head;
};


#endif //SOCIETY_SCENE_H
