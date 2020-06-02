//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_APPENDAGE_H
#define SOCIETY_APPENDAGE_H

#include <glm/glm.hpp>
#include <vector>

#include "collision/Body.h"
#include "Joint.h"
#include "macros.h"


class Appendage : std::enable_shared_from_this<Appendage> {
public:
    POINTERIZE(Appendage);

    enum Shape {
        SPHERE,
        CYLINDER,
        BOX,
        OVAL
    };

    Appendage(const glm::vec3 &orientation, const glm::vec3 &dimensions, const glm::vec3 &infinitesimalDims, Shape shape);

    void link(const Ptr& part);

    const std::vector<glm::vec3> &getSurfacePoints() const;
private:
    glm::vec3 orientation;
    glm::vec3 dimensions;
    glm::vec3 infinitesimalDims;
    std::vector<glm::vec3> surfacePoints;
    std::vector<Joint::Ptr> joints;
    Body body;
    Shape shape;

    void generateSurfacePoints();
};


#endif //SOCIETY_APPENDAGE_H
