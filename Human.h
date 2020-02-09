//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_HUMAN_H
#define HIVEMIND_HUMAN_H


#include <queue>
#include <memory>

#include "MapActor.h"
#include "MapPosition.h"
#include "VisionMap.h"


class Human : public MapActor {
public:
    explicit Human(MapPosition position);

    void update() override;
private:
    VisionMap::Ptr visionMap;
};


#endif //HIVEMIND_HUMAN_H
