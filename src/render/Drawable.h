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
    PTR(Drawable);

    virtual std::string get_texture() const = 0;
    virtual GLuint get_vertex_array_id() const = 0;
    virtual unsigned int get_num_indices() const = 0;
    virtual GLenum get_draw_mode() const = 0;
};


#endif //SOCIETY_DRAWABLE_H
