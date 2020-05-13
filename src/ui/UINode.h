//
// Created by Philip on 5/13/2020.
//

#ifndef SOCIETY_UINODE_H
#define SOCIETY_UINODE_H

#include <common/TreeNode.h>
#include <memory>


class UINode : public TreeNode {
public:
    typedef std::shared_ptr<UINode> Ptr;
};

#endif //SOCIETY_UINODE_H
