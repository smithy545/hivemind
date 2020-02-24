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

    explicit Human(std::string name);

    void update() override;

    const std::string &getName() const;

    const VisionMap::Ptr &getVisionMap() const;

    const std::unordered_map<std::string, Relationship::Ptr> &getRelationships() const;

    const BaseRole::Ptr & getRole() const;

    const std::string &getCurrentTask() const;

private:
    std::string name;
    VisionMap::Ptr visionMap;
    std::unordered_map<std::string, Relationship::Ptr> relationships;
    BaseRole::Ptr role;
    std::string currentTask;
};


#endif //HIVEMIND_HUMAN_H
