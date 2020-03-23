//
// Created by smith on 3/23/2020.
//

#ifndef SOCIETY_STAGE_H
#define SOCIETY_STAGE_H

#include <vector>

#include "Entity.h"


class Stage {
public:
    json get(unsigned int id);

    void put(json entity);

private:
    std::vector<json> entities;
};


#endif //SOCIETY_STAGE_H
