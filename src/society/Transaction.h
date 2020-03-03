//
// Created by Philip on 3/3/2020.
//

#ifndef SOCIETY_TRANSACTION_H
#define SOCIETY_TRANSACTION_H

#include <vector>

#include "world/Prop.h"
#include "ResourcePool.h"


class Transaction {
private:
    std::vector<ResourcePool> availablePools;
    std::vector<Prop::Ptr> inputs;
    Prop::Ptr output;
};


#endif //SOCIETY_TRANSACTION_H
