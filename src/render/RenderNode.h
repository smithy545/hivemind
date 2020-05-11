//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RENDERNODE_H
#define SOCIETY_RENDERNODE_H

#include <GL/glew.h>
#include <memory>
#include <string>
#include <vector>

#include "RenderEntity.h"


class RenderNode {
public:
    typedef std::shared_ptr<RenderNode> Ptr;

    RenderNode(std::string spriteName, std::string shaderName);

    RenderNode(std::string spriteName, std::string shaderName, Ptr next);

    const Ptr &getNext() const;

    void setNext(const Ptr &next);

    const std::vector<RenderEntity> &getChildren() const;

    const std::string &getSpriteName() const;

    const std::string &getShaderName() const;

    void setShaderName(const std::string &shaderName);

    GLenum getMode() const;

    void setMode(GLenum mode);

    void addChild(float x, float y);

    void addChild(float x, float y, float angle);

private:
    std::vector<RenderEntity> children{};
    std::string shaderName;
    std::string spriteName;
    GLenum mode;
    Ptr next;
};


#endif //SOCIETY_RENDERNODE_H