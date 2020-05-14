//
// Created by Philip on 5/13/2020.
//

#ifndef SOCIETY_INTERFACENODE_H
#define SOCIETY_INTERFACENODE_H

#include <memory>

#include "common/TreeNode.h"


class InterfaceNode : public TreeNode {
public:
    typedef std::shared_ptr<InterfaceNode> Ptr;
};

#endif //SOCIETY_INTERFACENODE_H
