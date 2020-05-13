//
// Created by smith on 4/12/2020.
//
#include "RenderNode.h"

#include <utility>


RenderNode::RenderNode(std::string spriteName, std::string shaderName) : RenderNode(
        std::move(spriteName),
        std::move(shaderName),
        nullptr) {}

RenderNode::RenderNode(std::string spriteName, std::string shaderName, RenderNode::Ptr next) :
        spriteName(std::move(spriteName)),
        shaderName(std::move(shaderName)),
        next(std::move(next)),
        mode(GL_TRIANGLES) {}

LinkedNode::Ptr RenderNode::getNext() {
    return std::dynamic_pointer_cast<LinkedNode>(next);
}

void RenderNode::setNext(const RenderNode::Ptr &next) {
    RenderNode::next = next;
}

const std::vector<RenderEntity> &RenderNode::getChildren() const {
    return children;
}

const std::string &RenderNode::getSpriteName() const {
    return spriteName;
}


const std::string &RenderNode::getShaderName() const {
    return shaderName;
}

void RenderNode::setShaderName(const std::string &shaderName) {
    RenderNode::shaderName = shaderName;
}

void RenderNode::addChild(float x, float y) {
    children.emplace_back(glm::vec3(x, y, 0));
}

void RenderNode::addChild(float x, float y, float angle) {
    children.emplace_back(glm::vec3(x, y, 0), angle);
}

unsigned int RenderNode::getMode() const {
    return mode;
}

void RenderNode::setMode(unsigned int mode) {
    RenderNode::mode = mode;
}
