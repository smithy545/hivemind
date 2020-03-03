//
// Created by Philip on 3/3/2020.
//

#ifndef SOCIETY_SERVICEROLE_H
#define SOCIETY_SERVICEROLE_H

#include <memory>

#include "BaseRole.h"


// A role that provides services
class ServiceRole : public BaseRole {
public:
    typedef std::shared_ptr<ServiceRole> Ptr;
};


#endif //SOCIETY_SERVICEROLE_H
