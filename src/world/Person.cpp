//
// Created by Philip on 6/1/2020.
//

#include "Person.h"

#include "util/MathUtil.h"


const std::string &Person::getName() const {
    return name;
}

const glm::vec3 &Person::getPosition() const {
    return position;
}

void Person::setPosition(const glm::vec3 &position) {
    Person::position = position;
}

void Person::BodyPart::generateSurfacePoints() {
    // generate surface points based on shape class
    // comments show how the dimensions 3-vector corresponds to the shape dimensions. 0 means the value goes unused
    // infintesimal dimensions correspond to the step size during iteration of the dimensions in the dimensions vector
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
