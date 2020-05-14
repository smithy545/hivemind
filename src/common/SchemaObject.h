//
// Created by Philip on 3/7/2020.
//

#ifndef SOCIETY_SCHEMAOBJECT_H
#define SOCIETY_SCHEMAOBJECT_H

#include <memory>
#include <nlohmann/json-schema.hpp>
#include <utility>


using nlohmann::json;
using nlohmann::json_schema::json_validator;

class SchemaObject {
public:
    typedef std::shared_ptr<SchemaObject> Ptr;

    explicit SchemaObject(const std::string &schemaString);

    explicit SchemaObject(const json &schema);

    const json &getSchema() const;

    bool validate(const json &data);

private:
    const json schema;
    json_validator validator;
};


#endif //SOCIETY_SCHEMAOBJECT_H
