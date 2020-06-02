//
// Created by Philip on 6/1/2020.
//

#include "Scene.h"


Scene::Scene(int width, int height) : camera(0, 0, width, height) {
    renderHead = std::make_shared<RenderNode>("nude", "texture");

    auto testBody = std::make_shared<Body>();
    testBody->setAcceleration({0.01, 0.01, 0});
    addBody(testBody);

    collisionHead = std::make_shared<CollisionNode>(testBody, testBody);
}

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
