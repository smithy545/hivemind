//
// Created by Philip on 3/21/2020.
//

#include "SchemaEntity.h"

#include <iostream>
#include <util/FileUtil.h>


SchemaEntity::SchemaEntity(const std::string &schemaString) : SchemaEntity(json::parse(schemaString)) {}

SchemaEntity::SchemaEntity(const json &schema) : schema(schema) {
    try {
        validator.set_root_schema(schema);
    } catch (const std::exception &ex) {
        std::cerr << "Schema setup failed: " << ex.what() << std::endl;
    }
}

std::unordered_map<unsigned int, json> SchemaEntity::getChildren() {
    return children;
}

bool SchemaEntity::validate(const json &data) {
    try {
        validator.validate(data);
        return true;
    } catch (const std::exception &ex) {
        std::cerr << "Entity validation failed: " << ex.what() << std::endl;
        return false;
    }
}

unsigned int SchemaEntity::generate(const json &data) {
    if (validate(data)) {
        children[id++] = data;
        return id - 1;
    }
    return 0;
}

void SchemaEntity::destroy(unsigned int id) {
    if (children.find(id) != children.end())
        children.erase(id);
}

const json &SchemaEntity::getSchema() const {
    return schema;
}
