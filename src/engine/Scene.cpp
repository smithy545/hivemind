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


void Scene::add_to_scene(const std::string& shaderName, Mesh::Ptr mesh) {
    // add to render tree with body at origin
    _render_head = std::make_shared<RenderNode>(shaderName, std::move(mesh), _render_head);
    _render_head->add_body(std::make_shared<PhysicsBody>());
}
