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

void Scene::addToScene(const std::string& shaderName, const std::string& drawableId, const Body::Ptr& body) {
    // add collision nodes to check collision with existing entities
    for(const auto& entity: entities)
        collisionHead = std::make_shared<CollisionNode>(body, entity->getBody(), collisionHead, nullptr);

    // add collision node with self to ensure collision is found and object is passed to integrator
    collisionHead = std::make_shared<CollisionNode>(body, body, collisionHead, nullptr);

    // add to entities
    auto rect = std::make_shared<Rectangle>(0, 0, 10, 10);
    auto entity = std::make_shared<GameEntity>(rect, body);
    entities.push_back(entity);

    // add to render tree
    auto renderNode = renderHead;
    while(renderNode != nullptr) {
        if(renderNode->getShaderName() == shaderName)
            break;
        renderNode = std::dynamic_pointer_cast<RenderNode>(renderNode->getNext());
    }
    if(renderNode == nullptr)
        renderNode = std::make_shared<RenderNode>(shaderName, renderHead);

    renderNode->addChild(drawableId, body);
    renderHead = renderNode;
}
