//
// Created by Philip on 2/8/2020.
//

#ifndef HIVEMIND_CAMERA_H
#define HIVEMIND_CAMERA_H

#include <memory>

#include <glm/glm.hpp>

#include "src/pathing/MapNode.h"


class Camera {
public:
    typedef std::shared_ptr<Camera> Ptr;

    Camera(double x, double y, double width, double height, double tileSize);

    bool inSight(const MapNode::Ptr &node) const;

    void panLeft();

    void panRight();

    void panUp();

    void panDown();

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getWidth() const;

    void setWidth(double width);

    double getHeight() const;

    void setHeight(double height);

    double getTileSize() const;

    void setTileSize(double tileSize);

    glm::mat4 getViewMatrix();
private:
    double x;
    double y;
    double width;
    double height;
    double tileSize;
};


#endif //HIVEMIND_CAMERA_H
