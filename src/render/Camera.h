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

    Camera(float x, float y, float width, float height, float tileSize);

    bool inSight(const MapNode::Ptr &node) const;

    void panLeft();

    void panRight();

    void panUp();

    void panDown();

    void zoomIn();

    void zoomOut();

    float getX() const;

    float getY() const;

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

    float getTileSize() const;

    void setTileSize(double tileSize);

    float getScale() const;

    glm::mat4 getViewProjectionMatrix();

private:
    glm::vec2 pos;
    float width;
    float height;
    float scale;
    float tileSize;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};


#endif //HIVEMIND_CAMERA_H
