//
// Created by Philip on 5/13/2020.
//

#ifndef SOCIETY_DOUBLYLINKEDNODE_H
#define SOCIETY_DOUBLYLINKEDNODE_H

#include <memory>

#include "LinkedNode.h"


class DoublyLinkedNode : public LinkedNode {
public:
    typedef std::shared_ptr<DoublyLinkedNode> Ptr;

    virtual Ptr getPrevious() = 0;
};


#endif //SOCIETY_DOUBLYLINKEDNODE_H
