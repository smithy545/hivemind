//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RECTANGLE_H
#define SOCIETY_RECTANGLE_H


class Rectangle {
public:
    Rectangle(double width, double height);

    Rectangle(double x, double y, double width, double height);

    bool collides(double X, double Y) const;

    bool collides(Rectangle rect);

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

    const double *getPoints() const;

private:
    double x, y;
    double centerX, centerY;
    double width, height;
    double points[8]{};

    void calculatePoints();
};


#endif //SOCIETY_RECTANGLE_H
