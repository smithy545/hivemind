//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_QUADTREE_H
#define SOCIETY_QUADTREE_H

#include <vector>

#include "macros.h"
#include "Rectangle.h"


class QuadTree {
public:
    PTR(QuadTree);

    QuadTree(int level, Rectangle bounds);

    void clear();

    void split();

    int get_index(Rectangle pRect);

    void insert(Rectangle pRect);

    std::vector<Rectangle> retrieve(std::vector<Rectangle> return_objects, Rectangle pRect);
private:
    const int OBJECTS_PER_QUAD = 5;
    const int MAX_LEVELS = 5;

    int level;
    std::vector<Rectangle> objects;
    Rectangle bounds;
    Ptr nodes[4];
};


#endif //SOCIETY_QUADTREE_H
