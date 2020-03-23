//
// Created by Philip on 2/8/2020.
//

#ifndef SOCIETY_CAMERA_H
#define SOCIETY_CAMERA_H

#include <glm/glm.hpp>
#include <memory>
#include <pathing/MapNode.h>


class Camera {
public:
    typedef std::shared_ptr<Camera> Ptr;

    Camera(float x, float y, float width, float height);

    bool inSight(const MapNode::Ptr &node, int tileSize) const;

    void panLeft();

    void panRight();

    void panUp();

    void panDown();

    void zoomIn();

    void zoomOut();

    void resize(int width, int height);

    float getX() const;

    float getY() const;

    float getWidth() const;

    float getHeight() const;

    float getScale() const;

    glm::mat4 getViewProjectionMatrix();

private:
    glm::vec2 pos;
    float width;
    float height;
    float scale;

    // initialize matrices to identity
    glm::mat4 viewMatrix{1};
    glm::mat4 projectionMatrix{1};

    void resetProjectionMatrix();

    void resetViewMatrix();
};


#endif //SOCIETY_CAMERA_H
