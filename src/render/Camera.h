//
// Created by Philip on 2/8/2020.
//

#ifndef SOCIETY_CAMERA_H
#define SOCIETY_CAMERA_H

#include <glm/glm.hpp>
#include <memory>

#include "collision/Rectangle.h"


class Camera {
public:
    typedef std::shared_ptr<Camera> Ptr;

    Camera(double x, double y, double width, double height);

    bool inSight(double x, double y);

    void panLeft();

    void panRight();

    void panUp();

    void panDown();

    void zoomIn();

    void zoomOut();

    void resize(double width, double height);

    Rectangle getBoundingRect();

    double getScale() const;

    glm::mat4 getViewProjectionMatrix();

private:
    glm::vec3 pos;
    Rectangle bound;
    double scale{1.0};

    // initialize matrices to identity
    glm::mat4 viewMatrix{1};
    glm::mat4 projectionMatrix{1};

    void resetProjectionMatrix();

    void resetViewMatrix();
};


#endif //SOCIETY_CAMERA_H
