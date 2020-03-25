//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_SCHEMAENTITY_H
#define SOCIETY_SCHEMAENTITY_H

#include <iostream>
#include <memory>
#include <nlohmann/json-schema.hpp>
#include <utility>

using nlohmann::json;
using nlohmann::json_schema::json_validator;


class SchemaEntity {
public:
    typedef std::shared_ptr<SchemaEntity> Ptr;

    explicit SchemaEntity(const std::string &schemaString);

    explicit SchemaEntity(const json &schema);

    std::unordered_map<unsigned int, json> getChildren();

    bool validate(const json &data);
    unsigned int generate(const json &data);
    void destroy(unsigned int id);

private:
    const json schema;
    json_validator validator;

    int id{0};
    std::unordered_map<unsigned int, json> children;
};


#endif //SOCIETY_SCHEMAENTITY_H
