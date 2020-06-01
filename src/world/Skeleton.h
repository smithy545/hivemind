//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_SKELETON_H
#define SOCIETY_SKELETON_H

#include "macros.h"


class Skeleton {
public:
    POINTERIZE(Skeleton);

    class BodyPart {
    public:
    POINTERIZE(BodyPart);

        enum ShapeClass {
            SPHERE,
            CYLINDER,
            BOX,
            OVAL
        };

        glm::vec3 orientation;
        glm::vec3 dimensions;
        glm::vec3 infinitesimalDims;
        std::vector<glm::vec3> surfacePoints;
        Ptr parent;
        std::vector<Ptr> children;
        ShapeClass shape;

        void generateSurfacePoints();
    };
};


#endif //SOCIETY_SKELETON_H
