//
// Created by Philip on 6/1/2020.
//

#include "Scene.h"


Scene::Scene(int width, int height) : camera(width, height) {}

Camera &Scene::getCamera() {
    return camera;
}

RenderNode::Ptr Scene::getRenderTree() {
    return renderHead;
}

CollisionNode::Ptr Scene::getCollisionTree() {
    // kill nodes marked for removal
    auto node = collisionHead;
    CollisionNode::Ptr prev = nullptr;
    while(node != nullptr) {
        if (!node->isAlive()) {
            if (prev != nullptr)
                prev = node;
            else if (node->getNext() == nullptr) {
                collisionHead = nullptr;
                break;
            }
        } else if(prev != nullptr)
            prev->setNext(node->getNext());
        node = node->getNext();
    }

    return collisionHead;
}

void Scene::addToScene(const std::string& shaderName, Mesh::Ptr mesh, const Body::Ptr& body, bool physics) {
    if(physics) {
        // find end of collision list
        auto collisionNode = collisionHead;
        while (collisionNode != nullptr && collisionNode->getNext() != nullptr)
            collisionNode = collisionNode->getNext();

        // add collision node with self to ensure collision is found and object is passed to integrator
        auto selfCollision = std::make_shared<CollisionNode>(body, body);
        if (collisionNode == nullptr) {
            collisionHead = selfCollision;
            collisionNode = collisionHead;
        } else {
            collisionNode->setNext(selfCollision);
            collisionNode = collisionNode->getNext();
        }

        // add collision nodes to check collision with existing entities
        for (const auto &entity: entities) {
            collisionNode->setNext(std::make_shared<CollisionNode>(body, entity->getBody()));
            collisionNode = collisionNode->getNext();
        }
    }

    // add to render tree
    renderHead = std::make_shared<RenderNode>(shaderName, std::move(mesh), renderHead);
    renderHead->addChild(body);

    // add to entities
    auto rect = std::make_shared<Rectangle>(0, 0, 10, 10);
    auto entity = std::make_shared<GameEntity>(rect, body);
    entities.push_back(entity);
}
