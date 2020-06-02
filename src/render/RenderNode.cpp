//
// Created by smith on 4/12/2020.
//
#include "RenderNode.h"

#include <utility>


RenderNode::RenderNode(std::string spriteName, std::string shaderName, const GLenum &mode, Ptr next):
    spriteName(std::move(spriteName)),
    shaderName(std::move(shaderName)),
    next(std::move(next)),
    mode(mode) {}

LinkedNode::Ptr RenderNode::getNext() {
    return std::dynamic_pointer_cast<LinkedNode>(next);
}

void RenderNode::setNext(const RenderNode::Ptr &node) {
    next = node;
}

const std::vector<Body::Ptr> &RenderNode::getChildren() const {
    return children;
}

const std::string &RenderNode::getSpriteName() const {
    return spriteName;
}

const std::string &RenderNode::getShaderName() const {
    return shaderName;
}

void RenderNode::setShaderName(const std::string &name) {
    shaderName = name;
}

unsigned int RenderNode::getMode() const {
    return mode;
}

void RenderNode::setMode(unsigned int mode) {
    RenderNode::mode = mode;
}

void RenderNode::addChild(const Body::Ptr& body) {
    children.push_back(body);
}
