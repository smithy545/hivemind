//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RENDERNODE_H
#define SOCIETY_RENDERNODE_H

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "Camera.h"
#include "common/Body.h"
#include "common/LinkedNode.h"
#include "macros.h"
#include "Drawable.h"


class RenderNode : public LinkedNode {
public:
    explicit RenderNode(std::string shaderName, Drawable::Ptr entity, Ptr next = nullptr);

    LinkedNode::Ptr get_next() override;

    void set_next(const Ptr &node);

    void instance(const Body::Ptr& body);

    int prepare(const Camera& camera);

    VAR_GET(GLuint, instance_buffer, public){0};
    REFVAR_GET(std::vector<Body::Ptr>, instances, public);
    MVAR(std::string, shader_name, public, private);
    MVAR(Drawable::Ptr, entity, public, public);
private:
    Ptr next;
};


#endif //SOCIETY_RENDERNODE_H
