//
// Created by Philip on 6/1/2020.
//

#include "Appendage.h"

#include "util/MathUtil.h"


Appendage::Appendage(const glm::vec3 &orientation, const glm::vec3 &dimensions, const glm::vec3 &infinitesimalDims,
                     Shape shape)
        : orientation(orientation), dimensions(dimensions),
          infinitesimalDims(infinitesimalDims), shape(shape) {
    generateSurfacePoints();
}

void Appendage::link(const Appendage::Ptr& part) {
    auto joint = std::make_shared<Joint>(this->shared_from_this(), part);
    joints.push_back(joint);
}

const std::vector<glm::vec3> &Appendage::getSurfacePoints() const {
    return surfacePoints;
}

void Appendage::generateSurfacePoints() {
    // generate surface points based on shape class
    // comments show how the dimensions 3-vector corresponds to the shape dimensions. 0 means the value goes unused
    // infinitesimal dimensions correspond to the step size during iteration of the dimensions in the dimensions vector
    // TODO: Look into subclassing body parts according to shape class
    switch (shape) {
        case SPHERE:
            // dimensions: (x, y, z) = (radius, 0, 0)
            // infinitesimal: (x, y, z) = (0, dRho, dTheta)
            surfacePoints = MathUtil::generateSphere(dimensions.x, infinitesimalDims.y, infinitesimalDims.z);
            break;
        case CYLINDER:
            // dimensions: (x, y, z) = (radius, length, 0)
            // infinitesimal: (x, y, z) = (dR, dTheta)
            surfacePoints = MathUtil::generateCylinder(dimensions.x, dimensions.y, infinitesimalDims.x, infinitesimalDims.y);
            break;
        case BOX:
            // dimensions: (x, y, z) = (width, height, length)
            surfacePoints = MathUtil::generateBox(dimensions.x, dimensions.y, dimensions.z);
            break;
        case OVAL:
            // dimensions: (x, y, z) = (minor-axis radius, major-axis radius, 0)
            break;
    }
}
