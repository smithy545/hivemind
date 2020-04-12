//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RECTANGLE_H
#define SOCIETY_RECTANGLE_H


class Rectangle {
public:
    Rectangle(int width, int height);

    Rectangle(int x, int y, int width, int height);

    bool collides(int X, int Y);

    bool collides(Rectangle rect);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    const int *getPoints() const;

private:
    int x, y;
    int width, height;
    int points[8]{};

    void calculatePoints();
};


#endif //SOCIETY_RECTANGLE_H
