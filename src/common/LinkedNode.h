//
// Created by Philip on 5/13/2020.
//

#ifndef SOCIETY_LINKEDNODE_H
#define SOCIETY_LINKEDNODE_H

#include <memory>


class LinkedNode {
public:
    typedef std::shared_ptr<LinkedNode> Ptr;

    virtual Ptr getNext() = 0;
};


#endif //SOCIETY_LINKEDNODE_H
