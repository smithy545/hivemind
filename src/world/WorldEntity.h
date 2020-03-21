//
// Created by Philip on 2/9/2020.
//

#ifndef SOCIETY_WORLDENTITY_H
#define SOCIETY_WORLDENTITY_H

#include <memory>
#include <string>
#include <utility>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fmt/format.h>

#include "common/Entity.h"
#include "pathing/MapNode.h"


class WorldEntity : public Entity {
public:
    static unsigned int GLOBAL_ID;

    typedef std::shared_ptr<WorldEntity> Ptr;

    MapNode::Ptr &getPosition();

    void setPosition(MapNode::Ptr node);

    glm::mat4 getModel(int tileSize);

    int getX(int tileSize);

    int getY(int tileSize);

    int getX();

    int getY();

    int getWidth();

    int getHeight();

    unsigned int getId();

    std::string getIdString();

    const std::string &getSpriteName() const;

    void setSpriteName(const std::string &spriteName);

    json pack() override;

    bool unpack(json data) override;
protected:
    MapNode::Ptr position;
    std::string spriteName;

    explicit WorldEntity(std::string spriteName) : WorldEntity(std::move(spriteName), nullptr) {}

    WorldEntity(std::string spriteName, MapNode::Ptr initialLocation) : Entity(R"({"type": "object"})"_json),
                                                                        position(std::move(initialLocation)),
                                                                        spriteName(std::move(spriteName)),
                                                                        id(GLOBAL_ID++) {}

private:
    unsigned int id;
};

#endif //SOCIETY_WORLDENTITY_H
