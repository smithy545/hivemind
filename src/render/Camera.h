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

    void move_forward();

    void move_backword();

    void move_up();

    void move_down();

    void strafe_left();

    void strafe_right();

    void pan_left();

    void pan_right();

    void pan_up();

    void pan_down();

    void pan_horizontal(float speed);

    void pan_vertical(float speed);

    void zoom_in();

    void zoom_out();

    void resize(float width, float height);

    glm::mat4 get_view_projection_matrix() const;

    _VAR_GET(glm::vec3, up, public){glm::vec3(0, 1, 0)};
    _VAR_GET(glm::vec3,forward, public){glm::vec3(0, 0, -1)};
    _VAR_GET(glm::vec3, position, public){0};
    _VAR_GET(Rectangle, bounding_rect, public){Rectangle(0,0)};
private:
    float translation_speed{0.2f};
    float horizontal_rotation_speed{0.05f};
    float vertical_rotation_speed{0.05f};

    // initialize matrices to identity
    glm::mat4 view_matrix{1};
    glm::mat4 projection_matrix{1};

    void reset_projection_matrix();

    void reset_view_matrix();
};


#endif //SOCIETY_CAMERA_H
