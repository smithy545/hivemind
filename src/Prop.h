//
// Created by Philip on 2/12/2020.
//

#ifndef HIVEMIND_PROP_H
#define HIVEMIND_PROP_H

#include <memory>

#include "MapEntity.h"


class Prop : public MapEntity {
public:
    typedef std::shared_ptr<Prop> Ptr;
};


#endif //HIVEMIND_PROP_H
