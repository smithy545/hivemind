//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_SCENE_H
#define SOCIETY_SCENE_H

#include <vector>

#include "collision/CollisionNode.h"
#include "GameEntity.h"
#include "render/Camera.h"
#include "render/RenderNode.h"


class Scene {
public:
    Scene(int width, int height);

    Camera::Ptr &getCamera();

    RenderNode::Ptr getRenderTree();

    CollisionNode::Ptr getCollisionTree();

    void addToScene(const std::string& shaderName, const std::string& drawableId, const Body::Ptr& body, bool physics = false);
private:
    std::vector<GameEntity::Ptr> entities;
    Camera::Ptr camera;
    RenderNode::Ptr renderHead;
    CollisionNode::Ptr collisionHead;
};


#endif //SOCIETY_SCENE_H
