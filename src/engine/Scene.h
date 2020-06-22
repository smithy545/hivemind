//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_SCENE_H
#define SOCIETY_SCENE_H

#include <vector>

#include "collision/CollisionNode.h"
#include "render/Camera.h"
#include "render/Mesh.h"
#include "render/RenderNode.h"


class Scene {
public:
    Scene(int width, int height);

    void cleanup();

    Camera &getCamera();

    RenderNode::Ptr getRenderTree();

    CollisionNode::Ptr getCollisionTree();

    void addToScene(const std::string& shaderName, Mesh::Ptr mesh, const Body::Ptr& body, bool physics = false);
private:
    Camera camera;
    RenderNode::Ptr renderHead;
    CollisionNode::Ptr collisionHead;
};


#endif //SOCIETY_SCENE_H
