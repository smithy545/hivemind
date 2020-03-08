//
// Created by Philip on 2/12/2020.
//

#ifndef SOCIETY_PROP_H
#define SOCIETY_PROP_H

#include <memory>
#include <utility>

#include "WorldEntity.h"


class Prop : public WorldEntity {
public:
    typedef std::shared_ptr<Prop> Ptr;

    explicit Prop(std::string name) : Prop(std::move(name), 1) {}

    Prop(std::string name, int count) : name(std::move(name)), count(count) {}

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        this->name = name;
    }

    int getCount() const {
        return count;
    }

    void setCount(int count) {
        this->count = count;
    }

private:
    std::string name;
    int count;
};


#endif //SOCIETY_PROP_H
