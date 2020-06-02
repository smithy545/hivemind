//
// Created by Philip on 6/1/2020.
//

#include "Scene.h"


Scene::Scene(int width, int height) : camera(0, 0, width, height) {}

Camera &Scene::getCamera() {
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
