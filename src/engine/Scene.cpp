//
// Created by Philip on 6/1/2020.
//

#include "Scene.h"


Scene::Scene(int width, int height) : _camera(std::make_shared<Camera>(width, height)) {}

void Scene::cleanup() {
    // destroy references to render objects so their constructors are called
    while(_render_head != nullptr) {
        auto node = std::dynamic_pointer_cast<RenderNode>(_render_head->get_next());
        _render_head->set_next(nullptr);
        _render_head = node;
    }
}

CollisionNode::Ptr Scene::get_collision_tree() {
    // kill nodes marked for removal
    auto node = collision_head;
    CollisionNode::Ptr prev = nullptr;
    while(node != nullptr) {
        if (!node->is_alive()) {
            if (prev != nullptr) {
                prev->set_next(node->get_next());
            } else {
                collision_head = node->get_next();
                if(collision_head == nullptr)
                    break;
            }
        }
        node = node->get_next();
        prev = node;
    }

    return collision_head;
}

void Scene::add_to_scene(const std::string& shaderName, Mesh::Ptr mesh, const Body::Ptr& body, bool physics) {
    if(physics) {
        // find end of collision list
        auto collision_node = collision_head;
        while (collision_node != nullptr && collision_node->get_next() != nullptr)
            collision_node = collision_node->get_next();

        // add collision node with self to ensure collision is found and object is passed to integrator
        auto self_collision = std::make_shared<CollisionNode>(body, body);
        if (collision_node == nullptr) {
            collision_head = self_collision;
            collision_node = collision_head;
        } else {
            collision_node->set_next(self_collision);
            collision_node = collision_node->get_next();
        }
    }

    // add to render tree
    _render_head = std::make_shared<RenderNode>(shaderName, std::move(mesh), _render_head);
    _render_head->add_body(body);
}
