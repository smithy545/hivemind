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

    virtual std::string getTexture() = 0;
    virtual GLuint getVertexArrayId() = 0;
    virtual unsigned int getNumIndices() = 0;
    virtual GLenum getDrawMode() = 0;
};


#endif //SOCIETY_DRAWABLE_H
