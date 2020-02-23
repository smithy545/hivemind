//
// Created by Philip on 2/18/2020.
//

#ifndef HIVEMIND_INSTITUTION_H
#define HIVEMIND_INSTITUTION_H

#include <string>
#include <vector>

#include "BaseRole.h"

class Institution {
public:
    Institution(std::string name);

    const std::string &getName() const {
        return name;
    }

    const std::vector<BaseRole::Ptr> &getRoles() const {
        return roles;
    }

private:
    std::string name;
    std::vector<BaseRole::Ptr> roles;
};


#endif //HIVEMIND_INSTITUTION_H
