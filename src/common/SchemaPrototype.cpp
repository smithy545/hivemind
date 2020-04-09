//
// Created by Philip on 3/21/2020.
//

#include "SchemaPrototype.h"

#include <iostream>
#include <utility>
#include <util/FileUtil.h>


SchemaPrototype::SchemaPrototype(const std::string &schemaString) : SchemaPrototype(json::parse(schemaString)) {}

SchemaPrototype::SchemaPrototype(const json &schema) : schema(schema) {
    try {
        validator.set_root_schema(schema);
    } catch (const std::exception &ex) {
        std::cerr << "Schema setup failed: " << ex.what() << std::endl;
    }
}

std::unordered_map<unsigned int, json> SchemaPrototype::getChildren() {
    return children;
}

json SchemaPrototype::get(unsigned int id) {
    if (children.find(id) != children.end())
        return children[id];
    return nullptr;
}

bool SchemaPrototype::validate(const json &data) {
    try {
        validator.validate(data);
        return true;
    } catch (const std::exception &ex) {
        std::cerr << "Entity validation failed: " << ex.what() << std::endl;
        return false;
    }
}

unsigned int SchemaPrototype::generate(json &data) {
    if (validate(data)) {
        children[id++] = std::move(data);
        return id - 1;
    }
    return 0;
}

void SchemaPrototype::destroy(unsigned int id) {
    if (children.find(id) != children.end())
        children.erase(id);
}

const json &SchemaPrototype::getSchema() const {
    return schema;
}

void SchemaPrototype::set(unsigned int id, const std::string &key, json data) {
    if (children.find(id) != children.end())
        children[id][key] = std::move(data);
}