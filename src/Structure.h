//
// Created by Philip on 2/12/2020.
//

#ifndef HIVEMIND_STRUCTURE_H
#define HIVEMIND_STRUCTURE_H


#include <memory>

#include "GridMap.h"
#include "MapActor.h"


class Structure : public MapActor {
public:
    typedef std::shared_ptr<Structure> Ptr;

    void update(GridMap::Ptr map) override;
};


#endif //HIVEMIND_STRUCTURE_H
