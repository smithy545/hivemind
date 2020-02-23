//
// Created by philip on 1/23/20.
//

#ifndef HIVEMIND_HUMAN_H
#define HIVEMIND_HUMAN_H


#include <queue>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "MapActor.h"
#include "MapPosition.h"
#include "VisionMap.h"
#include "BaseRole.h"


class Human : public MapActor {
public:
    typedef std::shared_ptr<Human> Ptr;

    class Relationship {
    public:
        typedef std::shared_ptr<Relationship> Ptr;

        enum Type {
            TRANSACTIONAL,
            ROMANTIC,
            PLATONIC
        };

        Relationship(Human::Ptr person) : person(std::move(person)) {}

    private:
        double transactionalStrength{0.0};
        double romanticStrength{0.0};
        double platonicStrength{0.0};

        Human::Ptr person;
    };

    Human(const MapPosition& initialPosition);

    void update() override;

private:
    VisionMap::Ptr visionMap;
    std::unordered_map<std::string, Relationship::Ptr> relationships;
    BaseRole::Ptr role;
    std::string currentTask;
};


#endif //HIVEMIND_HUMAN_H
