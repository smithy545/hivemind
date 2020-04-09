//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_SCHEMAPROTOTYPE_H
#define SOCIETY_SCHEMAPROTOTYPE_H

#include <iostream>
#include <memory>
#include <nlohmann/json-schema.hpp>
#include <utility>

using nlohmann::json;
using nlohmann::json_schema::json_validator;


class SchemaPrototype {
public:
    typedef std::shared_ptr<SchemaPrototype> Ptr;

    explicit SchemaPrototype(const std::string &schemaString);

    explicit SchemaPrototype(const json &schema);

    std::unordered_map<unsigned int, json> getChildren();

    json get(unsigned int id);

    const json &getSchema() const;

    bool validate(const json &data);

    unsigned int generate(json &data);

    void destroy(unsigned int id);

    void set(unsigned int id, const std::string &key, json data);

private:
    const json schema;
    json_validator validator;

    int id{1};
    std::unordered_map<unsigned int, json> children;
};


#endif //SOCIETY_SCHEMAPROTOTYPE_H
