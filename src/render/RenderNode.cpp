//
// Created by smith on 4/12/2020.
//
#include "RenderNode.h"

#include <utility>


RenderNode::RenderNode(std::string shader_name, Drawable::Ptr entity, Ptr next):
    _shader_name(std::move(shader_name)),
    _entity(std::move(entity)),
    next(std::move(next)) {}

LinkedNode::Ptr RenderNode::get_next() {
    return std::dynamic_pointer_cast<LinkedNode>(next);
}

void RenderNode::set_next(const RenderNode::Ptr &node) {
    next = node;
}

void RenderNode::add_body(const Body::Ptr& body) {
    _bodies.push_back(body);
}
