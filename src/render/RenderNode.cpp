//
// Created by smith on 4/12/2020.
//
#include "RenderNode.h"

#include <utility>

#include <iostream>
RenderNode::RenderNode(std::string shader_name, Drawable::Ptr entity, Ptr next):
    _shader_name(std::move(shader_name)),
    _entity(std::move(entity)),
    next(std::move(next)) {
    std::cout << "test1" << std::endl;
    glBindVertexArray(_entity->get_vertex_array_id());
    std::cout << "test2" << std::endl;

    glGenBuffers(1, &_instance_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _instance_buffer);
    std::cout << "test3" << std::endl;

    // vertex attributes (we actually use the stride column!)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(1 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));
    std::cout << "test4" << std::endl;

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    std::cout << "test5" << std::endl;

    glBindVertexArray(0);
}

LinkedNode::Ptr RenderNode::get_next() {
    return std::dynamic_pointer_cast<LinkedNode>(next);
}

void RenderNode::set_next(const RenderNode::Ptr &node) {
    next = node;
}

int RenderNode::get_num_instances() {
    return _instance_matrices.size();
}

void RenderNode::instance(const Body::Ptr& body) {
    _instances.push_back(body);
}

void RenderNode::prepare() {
    _instance_matrices.clear();
    for(const auto& body: _instances)
        _instance_matrices.push_back(body->get_model_matrix());

    glBindBuffer(GL_ARRAY_BUFFER, _instance_buffer);
    glBufferData(GL_ARRAY_BUFFER, _instance_matrices.size()*sizeof(glm::mat4), &_instance_matrices[0], GL_STATIC_DRAW);
}
