//
// Created by smith on 4/12/2020.
//
#include "RenderNode.h"

#include <utility>


RenderNode::RenderNode(std::string shaderName, Ptr next):
    shaderName(std::move(shaderName)),
    next(std::move(next)) {}

LinkedNode::Ptr RenderNode::getNext() {
    return std::dynamic_pointer_cast<LinkedNode>(next);
}

void RenderNode::setNext(const RenderNode::Ptr &node) {
    next = node;
}

const std::unordered_map<std::string, std::vector<Body::Ptr>> &RenderNode::getChildren() const {
    return bodies;
}

const std::string &RenderNode::getShaderName() const {
    return shaderName;
}

void RenderNode::setShaderName(const std::string &name) {
    shaderName = name;
}

void RenderNode::addChild(const std::string& drawableId, const Body::Ptr& body) {
    if(bodies.find(drawableId) == bodies.end())
        bodies[drawableId] = {body};
    else
        bodies[drawableId].push_back(body);
}
