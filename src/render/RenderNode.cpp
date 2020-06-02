//
// Created by smith on 4/12/2020.
//
#include "RenderNode.h"

#include <utility>


RenderNode::RenderNode(std::string shaderName, const GLenum &mode, Ptr next):
    shaderName(std::move(shaderName)),
    next(std::move(next)),
    mode(mode) {}

LinkedNode::Ptr RenderNode::getNext() {
    return std::dynamic_pointer_cast<LinkedNode>(next);
}

void RenderNode::setNext(const RenderNode::Ptr &node) {
    next = node;
}

const std::unordered_map<std::string, std::vector<Body::Ptr>> &RenderNode::getChildren() const {
    return spriteBodies;
}

const std::string &RenderNode::getShaderName() const {
    return shaderName;
}

void RenderNode::setShaderName(const std::string &name) {
    shaderName = name;
}

unsigned int RenderNode::getDrawMode() const {
    return mode;
}

void RenderNode::setDrawMode(unsigned int newMode) {
    mode = newMode;
}

void RenderNode::addChild(const std::string& spriteName, const Body::Ptr& body) {
    if(spriteBodies.find(spriteName) == spriteBodies.end())
        spriteBodies[spriteName] = {body};
    else
        spriteBodies[spriteName].push_back(body);
}
