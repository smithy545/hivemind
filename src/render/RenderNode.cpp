//
// Created by smith on 4/12/2020.
//
#include "RenderNode.h"

#include <utility>


RenderNode::RenderNode(std::string shaderName, Drawable::Ptr entity, Ptr next):
    shaderName(std::move(shaderName)),
    entity(std::move(entity)),
    next(std::move(next)) {}

LinkedNode::Ptr RenderNode::getNext() {
    return std::dynamic_pointer_cast<LinkedNode>(next);
}

void RenderNode::setNext(const RenderNode::Ptr &node) {
    next = node;
}

const std::vector<Body::Ptr> &RenderNode::getChildren() const {
    return bodies;
}

const std::string &RenderNode::getShaderName() const {
    return shaderName;
}

void RenderNode::setShaderName(const std::string &name) {
    shaderName = name;
}

void RenderNode::addChild(const Body::Ptr& body) {
    bodies.push_back(body);
}

Drawable::Ptr RenderNode::getEntity() {
    return entity;
}

void RenderNode::setEntity(Drawable::Ptr entity) {
    this->entity = std::move(entity);
}
