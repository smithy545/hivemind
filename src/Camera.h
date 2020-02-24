//
// Created by Philip on 2/8/2020.
//

#ifndef HIVEMIND_CAMERA_H
#define HIVEMIND_CAMERA_H

#include <memory>

#include "MapNode.h"


class Camera {
public:
    typedef std::shared_ptr<Camera> Ptr;

    double x;
    double y;
    double width;
    double height;

    Camera(double x, double y, double width, double height);

    bool inSight(const MapNode::Ptr &node);
};


#endif //HIVEMIND_CAMERA_H
