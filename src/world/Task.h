//
// Created by Philip on 7/8/2020.
//

#ifndef SOCIETY_TASK_H
#define SOCIETY_TASK_H

#include "macros.h"


class Task {
public:
    virtual void operator()() = 0;
};


#endif //SOCIETY_TASK_H
