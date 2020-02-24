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

    Camera(double x, double y, double width, double height);

    bool inSight(const MapNode::Ptr &node) const;

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getWidth() const;

    void setWidth(double width);

    double getHeight() const;

    void setHeight(double height);

private:
    double x;
    double y;
    double width;
    double height;
};


#endif //HIVEMIND_CAMERA_H
