//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_SCENE_H
#define SOCIETY_SCENE_H

#include <vector>

#include "collision/Body.h"
#include "collision/CollisionNode.h"
#include "render/Camera.h"
#include "render/RenderNode.h"


class Scene {
public:
    Scene(int width, int height);

    Camera::Ptr &getCamera();

    const RenderNode::Ptr &getRenderTree() const;

    const CollisionNode::Ptr &getCollisionTree() const;

    void addToScene(const std::string& spriteName, const std::string& shaderName, const GLenum &mode, const Body::Ptr& body);
private:
    std::vector<Body::Ptr> bodies;
    Camera::Ptr camera;
    RenderNode::Ptr renderHead;
    CollisionNode::Ptr collisionHead;
};


#endif //SOCIETY_SCENE_H
