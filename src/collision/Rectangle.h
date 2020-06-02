//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RECTANGLE_H
#define SOCIETY_RECTANGLE_H

#include "macros.h"
#include "Polygon.h"

class Rectangle : public Polygon, public std::enable_shared_from_this<Rectangle> {
public:
    POINTERIZE(Rectangle);

    Rectangle(double width, double height);

    Rectangle(double x, double y, double width, double height);

    bool collides(double X, double Y) const;

    bool collides(Shape::Ptr other) override;

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getCenterX() const;

    void setCenterX(double centerX);

    double getCenterY() const;

    void setCenterY(double centerY);

    double getWidth() const;

    void setWidth(double width);

    double getHeight() const;

    void setHeight(double height);

    std::vector<glm::vec2> getPoints() override;

private:
    double x, y;
    double centerX, centerY;
    double width, height;
    std::vector<glm::vec2> points{4};

    void calculatePoints();
};


#endif //SOCIETY_RECTANGLE_H
