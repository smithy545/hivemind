//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_ENTITY_H
#define SOCIETY_ENTITY_H

#include <iostream>
#include <nlohmann/json-schema.hpp>
#include <utility>

using nlohmann::json;


class Entity {
public:
    explicit Entity(json schema);

    virtual bool unpack(json data) = 0;

    virtual json pack() = 0;

    bool validate();

    bool storeToFile(const std::string &filePath);

    bool loadFromFile(const std::string &filePath);

private:
    const json schema;
};


#endif //SOCIETY_ENTITY_H
