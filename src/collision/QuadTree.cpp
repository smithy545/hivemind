//
// Created by smith on 4/12/2020.
// QuadTree ref: https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
//

#include "QuadTree.h"

using std::make_shared;


QuadTree::QuadTree(int pLevel, Rectangle pBounds) : level(pLevel), bounds(pBounds) {}

void QuadTree::clear() {
    objects.clear();

    for (auto &node : nodes) {
        if (node != nullptr) {
            node->clear();
            node = nullptr;
        }
    }
}

void QuadTree::split() {
    int subWidth = (int) (bounds.getWidth() / 2);
    int subHeight = (int) (bounds.getHeight() / 2);
    int x = (int) bounds.getX();
    int y = (int) bounds.getY();


    nodes[1] = make_shared<QuadTree>(level + 1, Rectangle(x, y, subWidth, subHeight));
    nodes[0] = make_shared<QuadTree>(level + 1, Rectangle(x + subWidth, y, subWidth, subHeight));
    nodes[2] = make_shared<QuadTree>(level + 1, Rectangle(x, y + subHeight, subWidth, subHeight));
    nodes[3] = make_shared<QuadTree>(level + 1, Rectangle(x + subWidth, y + subHeight, subWidth, subHeight));
}

/*
 * Determine which node the object belongs to. -1 means
 * object cannot completely fit within a child node and is part
 * of the parent node
 */
int QuadTree::getIndex(Rectangle pRect) {
    int index = -1;
    double verticalMidpoint = bounds.getX() + (bounds.getWidth() / 2.0);
    double horizontalMidpoint = bounds.getY() + (bounds.getHeight() / 2.0);

    // Object can completely fit within the top quadrants
    bool topQuadrant = (pRect.getY() < horizontalMidpoint && pRect.getY() + pRect.getHeight() < horizontalMidpoint);
    // Object can completely fit within the bottom quadrants
    bool bottomQuadrant = (pRect.getY() > horizontalMidpoint);

    // Object can completely fit within the left quadrants
    if (pRect.getX() < verticalMidpoint && pRect.getX() + pRect.getWidth() < verticalMidpoint) {
        if (topQuadrant) {
            index = 1;
        } else if (bottomQuadrant) {
            index = 2;
        }
    }
        // Object can completely fit within the right quadrants
    else if (pRect.getX() > verticalMidpoint) {
        if (topQuadrant) {
            index = 0;
        } else if (bottomQuadrant) {
            index = 3;
        }
    }

    return index;
}

void QuadTree::insert(Rectangle pRect) {
    if (nodes[0] != nullptr) {
        int index = getIndex(pRect);

        if (index != -1) {
            nodes[index]->insert(pRect);

            return;
        }
    }

    objects.push_back(pRect);

    if (objects.size() > OBJECTS_PER_QUAD && level < MAX_LEVELS) {
        if (nodes[0] == nullptr) {
            split();
        }

        int i = 0;
        while (i < objects.size()) {
            int index = getIndex(objects[i]);
            if (index != -1) {
                nodes[index]->insert(objects[i]);
                objects.erase(objects.begin() + i);
            } else {
                i++;
            }
        }
    }
}

std::vector<Rectangle> QuadTree::retrieve(std::vector<Rectangle> returnObjects, Rectangle pRect) {
    int index = getIndex(pRect);
    if (index != -1 && nodes[0] != nullptr) {
        nodes[index]->retrieve(returnObjects, pRect);
    }

    for (auto obj: objects)
        returnObjects.push_back(obj);

    return returnObjects;
}
