//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RENDERNODE_H
#define SOCIETY_RENDERNODE_H

#include <memory>
#include <string>
#include <vector>

#include "RenderEntity.h"


class RenderNode {
public:
    typedef std::shared_ptr<RenderNode> Ptr;

    explicit RenderNode(const std::string &spriteName);

    RenderNode(const std::string &spriteName, Ptr next);

    const Ptr &getNext() const;

    void setNext(const Ptr &next);

    const std::vector<RenderEntity> &getChildren() const;

    const std::string &getSpriteName() const;

    void addChild(float x, float y);

    void addChild(float x, float y, float angle);

private:
    std::vector<RenderEntity> children{};
    std::string spriteName;
    Ptr next;
};


#endif //SOCIETY_RENDERNODE_H
