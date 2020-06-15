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
#include "Drawable.h"


class RenderNode : public LinkedNode {
public:
    POINTERIZE(RenderNode);

    explicit RenderNode(std::string shaderName, Drawable::Ptr entity, Ptr next = nullptr);

    LinkedNode::Ptr getNext() override;

    void setNext(const Ptr &node);

    const std::vector<Body::Ptr> &getBodies() const;

    const std::string &getShaderName() const;

    void setShaderName(const std::string &name);

    void addBody(const Body::Ptr& body);

    Drawable::Ptr getEntity();

    void setEntity(Drawable::Ptr entity);
private:
    std::string shaderName;
    std::vector<Body::Ptr> bodies;
    Drawable::Ptr entity;
    Ptr next;
};


#endif //SOCIETY_RENDERNODE_H
