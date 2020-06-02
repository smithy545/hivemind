//
// Created by Philip on 6/1/2020.
//

#include "Scene.h"


Scene::Scene(int width, int height) : camera(std::make_shared<Camera>(0, 0, width, height)) {
    renderHead = std::make_shared<RenderNode>("nude", "texture");
    renderHead->addChild(std::make_shared<Body>());
}

Camera::Ptr &Scene::getCamera() {
    return camera;
}

const RenderNode::Ptr &Scene::getRenderTree() const {
    return renderHead;
}

const CollisionNode::Ptr &Scene::getCollisionTree() const {
    return collisionHead;
}

void Scene::addBody(const Body::Ptr& body) {
    bodies.push_back(body);
    renderHead->addChild(body);
}
