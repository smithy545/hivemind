//
// Created by Philip on 3/3/2020.
//

#ifndef SOCIETY_PRODUCTIONROLE_H
#define SOCIETY_PRODUCTIONROLE_H

#include <memory>

#include "BaseRole.h"


// A role that produces goods
class ProductionRole : public BaseRole {
public:
    typedef std::shared_ptr<ProductionRole> Ptr;
};


#endif //SOCIETY_PRODUCTIONROLE_H
