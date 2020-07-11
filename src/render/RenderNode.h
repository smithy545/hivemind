//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RENDERNODE_H
#define SOCIETY_RENDERNODE_H

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/Body.h"
#include "common/LinkedNode.h"
#include "macros.h"
#include "Drawable.h"


class RenderNode : public LinkedNode {
public:
    POINTERIZE(RenderNode);

    explicit RenderNode(std::string shaderName, Drawable::Ptr entity, Ptr next = nullptr);

    LinkedNode::Ptr get_next() override;

    void set_next(const Ptr &node);

    void instance(const Body::Ptr& body);

    _MVAR_GETSET(std::string, shader_name, public, private);
    _REFVAR_GET(std::vector<Body::Ptr>, instances, public);
    _MVAR_GETSET(Drawable::Ptr, entity, public, public);
private:
    Ptr next;
};


#endif //SOCIETY_RENDERNODE_H
