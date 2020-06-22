//
// Created by Philip on 6/1/2020.
//

#include "Scene.h"


Scene::Scene(int width, int height) : camera(width, height) {}

void Scene::cleanup() {
    // destroy references to render objects so their constructors are called
    while(renderHead != nullptr) {
        auto node = std::dynamic_pointer_cast<RenderNode>(renderHead->getNext());
        renderHead->setNext(nullptr);
        renderHead = node;
    }
}

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
            else if (node->get_next() == nullptr) {
                collisionHead = nullptr;
                break;
            }
        } else if(prev != nullptr)
            prev->set_next(node->get_next());
        node = node->get_next();
    }

    return collisionHead;
}

void Scene::addToScene(const std::string& shaderName, Mesh::Ptr mesh, const Body::Ptr& body, bool physics) {
    if(physics) {
        // find end of collision list
        auto collisionNode = collisionHead;
        while (collisionNode != nullptr && collisionNode->get_next() != nullptr)
            collisionNode = collisionNode->get_next();

        // add collision node with self to ensure collision is found and object is passed to integrator
        auto selfCollision = std::make_shared<CollisionNode>(body, body);
        if (collisionNode == nullptr) {
            collisionHead = selfCollision;
            collisionNode = collisionHead;
        } else {
            collisionNode->set_next(selfCollision);
            collisionNode = collisionNode->get_next();
        }
    }

    // add to render tree
    renderHead = std::make_shared<RenderNode>(shaderName, std::move(mesh), renderHead);
    renderHead->addBody(body);

    // add to entities
    auto rect = std::make_shared<Rectangle>(0, 0, 10, 10);
    //auto entity = std::make_shared<GameEntity>(rect, body);
    //entities.push_back(entity);
}
