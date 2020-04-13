//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_QUADTREE_H
#define SOCIETY_QUADTREE_H

#include <collision/Rectangle.h>
#include <memory>
#include <vector>


class QuadTree {
public:
    typedef std::shared_ptr<QuadTree> Ptr;

    QuadTree(int pLevel, Rectangle pBounds);

    void clear();

    void split();

    int getIndex(Rectangle pRect);

    void insert(Rectangle pRect);

    std::vector<Rectangle> retrieve(std::vector<Rectangle> returnObjects, Rectangle pRect);

private:
    const int OBJECTS_PER_QUAD = 5;
    const int MAX_LEVELS = 5;

    int level;
    std::vector<Rectangle> objects;
    Rectangle bounds;
    QuadTree::Ptr nodes[4];

};


#endif //SOCIETY_QUADTREE_H
