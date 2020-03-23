//
// Created by smith on 3/23/2020.
//

#ifndef SOCIETY_STAGE_H
#define SOCIETY_STAGE_H

#include <string>
#include <unordered_map>

#include "Entity.h"


class Stage {
public:
    json get(unsigned int id);

    void put(unsigned int id, json entity);

private:
    std::unordered_map<unsigned int, json> entities;
};


#endif //SOCIETY_STAGE_H
