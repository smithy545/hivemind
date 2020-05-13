//
// Created by Philip on 5/13/2020.
//

#ifndef SOCIETY_TREENODE_H
#define SOCIETY_TREENODE_H

#include <memory>
#include <vector>


class TreeNode {
public:
    typedef std::shared_ptr<TreeNode> Ptr;

    virtual Ptr getParent() = 0;

    virtual std::vector<Ptr> getChildren() = 0;
};


#endif //SOCIETY_TREENODE_H
