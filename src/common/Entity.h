//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_ENTITY_H
#define SOCIETY_ENTITY_H

#include <iostream>
#include <memory>
#include <nlohmann/json-schema.hpp>
#include <utility>

using nlohmann::json;
using nlohmann::json_schema::json_validator;


class Entity {
public:
    typedef std::shared_ptr<Entity> Ptr;

    explicit Entity(const std::string &schemaString);

    explicit Entity(const json &schema);

    std::unordered_map<unsigned int, json> getData();

    bool validate(const json &data);
    unsigned int generate(const json &data);
    void destroy(unsigned int id);

private:
    const json schema;
    json_validator validator;

    int id{0};
    std::unordered_map<unsigned int, json> entities{};
};


#endif //SOCIETY_ENTITY_H
