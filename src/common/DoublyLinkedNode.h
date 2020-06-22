//
// Created by Philip on 5/13/2020.
//

#ifndef SOCIETY_DOUBLYLINKEDNODE_H
#define SOCIETY_DOUBLYLINKEDNODE_H

#include "macros.h"
#include "LinkedNode.h"


class DoublyLinkedNode : public LinkedNode {
public:
    POINTERIZE(DoublyLinkedNode);

    virtual Ptr get_previous() = 0;
};


#endif //SOCIETY_DOUBLYLINKEDNODE_H
