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
    // add to entities
    auto rect = std::make_shared<Rectangle>(0, 0, 10, 10);
    auto entity = std::make_shared<GameEntity>(rect, body);
    entities.push_back(entity);

    // add as collision so it will be picked up by the integrator
    collisionHead = std::make_shared<CollisionNode>(body, body, collisionHead, nullptr);

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
