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

    Camera(double width, double height);

    void move(glm::vec3 differential);

    void moveForward();

    void moveBackword();

    void moveUp();

    void moveDown();

    void setPosition(const glm::vec3 &position);

    void strafeLeft();

    void strafeRight();

    void panLeft();

    void panRight();

    void panUp();

    void panDown();

    void panHorizontal(float speed);

    void panVertical(float speed);

    void zoomIn();

    void zoomOut();

    void resize(float width, float height);

    glm::mat4 getViewProjectionMatrix() const;
private:
    _VAR(glm::vec3,up,public,private,glm::vec3(0, 1, 0));
    _VAR(glm::vec3,forward,public,private,glm::vec3(0, 0, -1));
    _VAR(glm::vec3,position,public,private,glm::vec3(0, 0, 0));
    _VAR(Rectangle,bounding_rect,public,private,Rectangle(0,0));
    float translationSpeed{0.2};
    float horizontalRotationSpeed{0.05};
    float verticalRotationSpeed{0.05};

    // initialize matrices to identity
    glm::mat4 viewMatrix{1};
    glm::mat4 projectionMatrix{1};

    void resetProjectionMatrix();

    void resetViewMatrix();
};


#endif //SOCIETY_CAMERA_H
