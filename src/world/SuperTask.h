//
// Created by Philip on 7/8/2020.
//

#ifndef SOCIETY_SUPERTASK_H
#define SOCIETY_SUPERTASK_H

#include <vector>

#include "macros.h"
#include "Task.h"

using std::vector;


class SuperTask : public Task {
private:
    vector<vector<Task>> preTasks;
};


#endif //SOCIETY_SUPERTASK_H
