//
// Created by Philip on 2/9/2020.
//

#ifndef SOCIETY_WORLDENTITY_H
#define SOCIETY_WORLDENTITY_H

#include <common/SchemaEntity.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <memory>
#include <pathing/MapNode.h>
#include <string>
#include <utility>


class WorldEntity : public SchemaEntity {
public:
    typedef std::shared_ptr<WorldEntity> Ptr;

    MapNode::Ptr &getPosition();

    void setPosition(MapNode::Ptr node);

protected:
    MapNode::Ptr position;
};

#endif //SOCIETY_WORLDENTITY_H
