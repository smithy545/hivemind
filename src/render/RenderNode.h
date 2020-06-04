//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RENDERNODE_H
#define SOCIETY_RENDERNODE_H

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "collision/Body.h"
#include "common/LinkedNode.h"
#include "macros.h"


class RenderNode : public LinkedNode {
public:
    POINTERIZE(RenderNode);

    explicit RenderNode(std::string shaderName, Ptr next = nullptr);

    LinkedNode::Ptr getNext() override;

    void setNext(const Ptr &node);

    const std::unordered_map<std::string, std::vector<Body::Ptr>> &getChildren() const;

    const std::string &getShaderName() const;

    void setShaderName(const std::string &name);

    void addChild(const std::string& spriteName, const Body::Ptr& body);
private:
    std::string shaderName;
    std::unordered_map<std::string, std::vector<Body::Ptr>> spriteBodies;
    Ptr next;
};


#endif //SOCIETY_RENDERNODE_H
