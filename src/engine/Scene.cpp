//
// Created by Philip on 6/1/2020.
//

#include "Scene.h"


Scene::Scene(int width, int height) : camera(std::make_shared<Camera>(width, height)) {}

Camera::Ptr &Scene::getCamera() {
    return camera;
}

const RenderNode::Ptr &Scene::getRenderTree() const {
    return renderHead;
}

const CollisionNode::Ptr &Scene::getCollisionTree() const {
    return collisionHead;
}

void Scene::addToScene(const std::string& spriteName, const std::string& shaderName, const GLenum &mode, const Body::Ptr& body) {
    auto node = renderHead;
    while(node != nullptr) {
        if(node->getSpriteName() == spriteName && node->getShaderName() == shaderName)
            break;
        node = std::dynamic_pointer_cast<RenderNode>(node->getNext());
    }
    if(node == nullptr)
        node = std::make_shared<RenderNode>(spriteName, shaderName, mode, renderHead);

    bodies.push_back(body);
    node->addChild(body);
    renderHead = node;
}
