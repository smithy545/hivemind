//
// Created by Philip on 5/13/2020.
//

#ifndef SOCIETY_TREENODE_H
#define SOCIETY_TREENODE_H

#include <vector>

#include "macros.h"


class TreeNode {
public:
    POINTERIZE(TreeNode);

    virtual Ptr getParent() = 0;

    virtual std::vector<Ptr> getChildren() = 0;
};


#endif //SOCIETY_TREENODE_H
