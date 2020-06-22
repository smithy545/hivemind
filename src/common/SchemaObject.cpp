//
// Created by Philip on 3/21/2020.
//

#include "SchemaObject.h"

#include <iostream>
#include <exception>


SchemaObject::SchemaObject(const std::string &schema_string) : SchemaObject(json::parse(schema_string)) {}

SchemaObject::SchemaObject(const json &schema) : _schema(schema) {
    try {
        validator.set_root_schema(schema);
    } catch (const std::exception &ex) {
        std::cerr << "Schema setup failed: " << ex.what() << std::endl;
    }
}

bool SchemaObject::validate(const json &data) {
    return validator.validate(data);
}
