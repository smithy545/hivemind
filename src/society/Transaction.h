//
// Created by Philip on 3/3/2020.
//

#ifndef SOCIETY_TRANSACTION_H
#define SOCIETY_TRANSACTION_H

#include <memory>
#include <vector>

#include "world/Prop.h"
#include "ResourcePool.h"

// Exchange of goods or services (maybe just goods we'll see) between humans
class Transaction {
public:
    typedef std::shared_ptr<Transaction> Ptr;
private:
    std::vector<ResourcePool> availablePools;
    std::vector<Prop::Ptr> inputs;
    Prop::Ptr output;
};


#endif //SOCIETY_TRANSACTION_H
