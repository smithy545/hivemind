//
// Created by smith on 4/12/2020.
//

#ifndef SOCIETY_QUADTREE_H
#define SOCIETY_QUADTREE_H

#include <common/Rectangle.h>
#include <common/SchemaObject.h>
#include <memory>
#include <vector>


class QuadTree {
public:
    typedef std::shared_ptr<QuadTree> Ptr;
private:
    const int OBJECTS_PER_QUAD = 5;
    const int MAX_LEVELS = 5;

    int level;
    std::vector<SchemaObject::Ptr> objects;
    Rectangle bounds;
    QuadTree::Ptr nodes[4];

    QuadTree(int pLevel, Rectangle pBounds) : level(pLevel), bounds(pBounds) {}
};


#endif //SOCIETY_QUADTREE_H
