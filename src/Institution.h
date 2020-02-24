//
// Created by Philip on 2/18/2020.
//

#ifndef HIVEMIND_INSTITUTION_H
#define HIVEMIND_INSTITUTION_H

#include <memory>
#include <string>
#include <vector>

#include "BaseRole.h"

class Institution {
public:
    typedef std::shared_ptr<Institution> Ptr;

    explicit Institution(std::string name);

    const std::string &getName() const {
        return name;
    }

    const std::vector<BaseRole::Ptr> &getRoles() const {
        return roles;
    }

    void setName(const std::string &name);

    void setRoles(const std::vector<BaseRole::Ptr> &roles);

private:
    std::string name;
    std::vector<BaseRole::Ptr> roles;
};


#endif //HIVEMIND_INSTITUTION_H
