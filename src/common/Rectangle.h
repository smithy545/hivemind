//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_RECTANGLE_H
#define SOCIETY_RECTANGLE_H


class Rectangle {
public:
    Rectangle(float width, float height);

    Rectangle(float x, float y, float width, float height);

    bool collides(float X, float Y);

    bool collides(Rectangle rect);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

    const float *getPoints() const;

private:
    int x, y;
    float width, height;
    float points[8]{};

    void calculatePoints();
};


#endif //SOCIETY_RECTANGLE_H
