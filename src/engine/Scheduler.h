//
// Created by Philip on 6/16/2020.
//

#ifndef SOCIETY_SCHEDULER_H
#define SOCIETY_SCHEDULER_H

#include <string>

#include "Stage.h"


class Scheduler {
public:
    virtual void addStage(Stage stage) = 0;
    virtual std::string schedule(void* job) = 0;
};


#endif //SOCIETY_SCHEDULER_H
