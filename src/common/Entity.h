//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_ENTITY_H
#define SOCIETY_ENTITY_H

#include <iostream>
#include <nlohmann/json-schema.hpp>
#include <utility>

using nlohmann::json;
using nlohmann::json_schema::json_validator;


class Entity {
public:
    explicit Entity(const json &schema);

    virtual json pack() = 0;

    virtual bool unpack(json data) = 0;

    bool validate();

    bool validate(const json &data);

    bool storeToFile(const std::string &filePath);

    bool loadFromFile(const std::string &filePath);

private:
    const json schema;
    json_validator validator;
};


#endif //SOCIETY_ENTITY_H
