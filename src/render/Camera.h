//
// Created by Philip on 2/8/2020.
//

#ifndef SOCIETY_CAMERA_H
#define SOCIETY_CAMERA_H

#include <memory>

#include <glm/glm.hpp>

#include "pathing/MapNode.h"


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

    void resize(int width, int height);

    void setTileSize(double tileSize);

    float getX() const;

    float getY() const;

    float getWidth() const;

    float getHeight() const;

    float getTileSize() const;

    float getScale() const;

    glm::mat4 getViewProjectionMatrix();

private:
    glm::vec2 pos;
    float width;
    float height;
    float scale;
    float tileSize;

    // initialize matrices to identity
    glm::mat4 viewMatrix{1};
    glm::mat4 projectionMatrix{1};

    void resetProjectionMatrix();

    void resetViewMatrix();
};


#endif //SOCIETY_CAMERA_H
