//
// Created by Philip on 2/18/2020.
//

#include "Institution.h"

Institution::Institution(std::string name) : name(std::move(name)) {
    // pass
}

void Institution::setName(const std::string &name) {
    this->name = name;
}

void Institution::setRoles(const std::vector<BaseRole::Ptr> &roles) {
    this->roles = roles;
}
