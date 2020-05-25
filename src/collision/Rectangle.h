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

    double getWidth() const;

    void setWidth(double width);

    double getHeight() const;

    void setHeight(double height);

    const double *getPoints() const;

private:
    int x, y;
    double width, height;
    double points[8]{};

    void calculatePoints();
};


#endif //SOCIETY_RECTANGLE_H
