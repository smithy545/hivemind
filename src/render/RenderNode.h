//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RENDERNODE_H
#define SOCIETY_RENDERNODE_H

#include <GL/glew.h>
#include <string>
#include <vector>

#include "collision/Body.h"
#include "common/LinkedNode.h"
#include "macros.h"


class RenderNode : public LinkedNode {
public:
    POINTERIZE(RenderNode);

    explicit RenderNode(std::string spriteName, std::string shaderName = "", const GLenum &mode = GL_TRIANGLES, Ptr next = nullptr);

    LinkedNode::Ptr getNext() override;

    void setNext(const Ptr &node);

    const std::vector<Body::Ptr> &getChildren() const;

    const std::string &getSpriteName() const;

    const std::string &getShaderName() const;

    void setShaderName(const std::string &name);

    GLenum getMode() const;

    void setMode(GLenum mode);

    void addChild(const Body::Ptr& body);
private:
    std::vector<Body::Ptr> children{};
    std::string shaderName;
    std::string spriteName;
    GLenum mode;
    Ptr next;
};


#endif //SOCIETY_RENDERNODE_H
