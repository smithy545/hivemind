//
// Created by Philip on 6/4/2020.
//

#ifndef SOCIETY_DRAWABLE_H
#define SOCIETY_DRAWABLE_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "macros.h"


class Drawable {
public:
    POINTERIZE(Drawable);

    virtual std::string get_texture() = 0;
    virtual GLuint get_vertex_array_id() = 0;
    virtual unsigned int get_num_indices() = 0;
    virtual GLenum get_draw_mode() = 0;
};


#endif //SOCIETY_DRAWABLE_H
