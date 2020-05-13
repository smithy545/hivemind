//
// Created by Philip on 2/25/2020.
//

#ifndef SOCIETY_INTERFACE_H
#define SOCIETY_INTERFACE_H

#include <common/SchemaObject.h>
#include <memory>
#include <render/Camera.h>
#include <render/Sprite.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "State.h"


class Interface {
public:
    typedef std::shared_ptr<Interface> Ptr;

    explicit Interface(const std::string &configPath);

    void addComponentAt(int x, int y, const std::string &componentType);

    void update(const State::Ptr &state);

    const std::unordered_map<std::string, SchemaObject::Ptr> &getComponents() const;

private:
    std::unordered_map<std::string, SchemaObject::Ptr> components;
    int tileId{0};
};


#endif //SOCIETY_INTERFACE_H
