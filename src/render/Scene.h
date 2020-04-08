//
// Created by smith on 4/8/2020.
//

#ifndef SOCIETY_SCENE_H
#define SOCIETY_SCENE_H

#include <memory>
#include <common/SchemaEntity.h>

#include "Camera.h"

class Scene {
public:
    typedef std::shared_ptr<Scene> Ptr;

    virtual std::vector<SchemaEntity::Ptr> getEntities() = 0;

    virtual Camera::Ptr &getCamera() = 0;
};


#endif //SOCIETY_SCENE_H
