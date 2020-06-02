//
// Created by Philip on 2/8/2020.
//

#ifndef SOCIETY_CAMERA_H
#define SOCIETY_CAMERA_H

#include <glm/glm.hpp>

#include "collision/Rectangle.h"
#include "macros.h"


class Camera {
public:
    POINTERIZE(Camera);

    Camera(double x, double y, double width, double height);

    bool inSight(double x, double y);

    bool inSight(glm::vec2 pos);

    bool inSight(const Rectangle& obj);

    void panLeft();

    void panRight();

    void panUp();

    void panDown();

    void zoomIn();

    void zoomOut();

    void resize(double width, double height);

    Rectangle getBoundingRect();

    float getScale() const;

    const glm::mat4 getViewProjectionMatrix() const;

private:
    glm::vec3 pos;
    Rectangle bound;
    float scale{1};

    // initialize matrices to identity
    glm::mat4 viewMatrix{1};
    glm::mat4 projectionMatrix{1};

    void resetProjectionMatrix();

    void resetViewMatrix();
};


#endif //SOCIETY_CAMERA_H
