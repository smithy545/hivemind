//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_SKELETON_H
#define SOCIETY_SKELETON_H

#include <vector>

#include "macros.h"
#include <glm/glm.hpp>


class Skeleton {
public:
    POINTERIZE(Skeleton);

    class Bone {
    public:
        POINTERIZE(Bone);
        glm::vec3 orientation;
        glm::vec3 dimensions;
        std::vector<Ptr> connected;
    };
};


#endif //SOCIETY_SKELETON_H
