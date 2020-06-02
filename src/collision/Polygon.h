//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_POLYGON_H
#define SOCIETY_POLYGON_H

#include <glm/glm.hpp>
#include <vector>

#include "macros.h"
#include "Shape.h"


class Polygon : public Shape {
public:
    POINTERIZE(Polygon);

    virtual std::vector<glm::vec2> getPoints() = 0;
};


#endif //SOCIETY_POLYGON_H
