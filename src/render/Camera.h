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

    Rectangle getBoundingRect();

    glm::mat4 getViewProjectionMatrix() const;

    const glm::vec3 &getPosition() const;

    const glm::vec3 &getForward() const;

    const glm::vec3 &getUp() const;
private:
    glm::vec3 up{0, 1, 0};
    glm::vec3 forward{0, 0, -1};
    glm::vec3 position{0, 0, 0};
    Rectangle bound;
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
