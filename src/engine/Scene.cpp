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

void Scene::addToScene(const std::string& shaderName, const std::string& spriteName, const GLenum &mode, const Body::Ptr& body) {
    // add to bodies
    bodies.push_back(body);

    // add to render tree
    auto node = renderHead;
    while(node != nullptr) {
        if(node->getShaderName() == shaderName)
            break;
        node = std::dynamic_pointer_cast<RenderNode>(node->getNext());
    }
    if(node == nullptr)
        node = std::make_shared<RenderNode>(shaderName, mode, renderHead);

    if(mode != node->getDrawMode())
        node->setDrawMode(mode);
    node->addChild(spriteName, body);
    renderHead = node;
}
