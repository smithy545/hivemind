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

    int get_num_instances();

    void instance(const Body::Ptr& body);

    void prepare();

    _VAR_GET(GLuint, instance_buffer, public);
    _REFVAR_GET(std::vector<Body::Ptr>, instances, public);
    _VAR_GET(std::vector<glm::mat4>, instance_matrices, public);
    _MVAR_GETSET(std::string, shader_name, public, private);
    _MVAR_GETSET(Drawable::Ptr, entity, public, public);
private:
    Ptr next;
};


#endif //SOCIETY_RENDERNODE_H
