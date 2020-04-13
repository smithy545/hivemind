//
// Created by smith on 4/12/2020.
//
#include "RenderNode.h"


RenderNode::RenderNode(const std::basic_string<char> &spriteName) : RenderNode(spriteName, nullptr) {}

RenderNode::RenderNode(const std::basic_string<char> &spriteName, Ptr next) : spriteName(spriteName), next(next) {}

const RenderNode::Ptr &RenderNode::getNext() const {
    return next;
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

void RenderNode::addChild(float x, float y) {
    children.emplace_back(glm::vec3(x, y, 0));
}

void RenderNode::addChild(float x, float y, float angle) {
    children.emplace_back(glm::vec3(x, y, 0), angle);
}
