//
// Created by Philip on 2/8/2020.
//

#ifndef HIVEMIND_CAMERA_H
#define HIVEMIND_CAMERA_H


#include "MapNode.h"

class Camera {
public:
    Camera(double x, double y, double width, double height);

    bool inSight(const MapNode::Ptr &node);

private:
    double x;
    double y;
    double width;
    double height;
};


#endif //HIVEMIND_CAMERA_H
