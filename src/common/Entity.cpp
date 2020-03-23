//
// Created by Philip on 3/21/2020.
//

#include "Entity.h"

#include <iostream>
#include <util/FileUtil.h>


Entity::Entity(const std::string &schemaString) : Entity(json::parse(schemaString)) {}

Entity::Entity(const json &schema) : schema(schema) {
    try {
        validator.set_root_schema(schema);
    } catch (const std::exception &ex) {
        std::cerr << "Schema setup failed: " << ex.what() << std::endl;
    }
}

std::unordered_map<unsigned int, json> Entity::getData() {
    return entities;
}

bool Entity::validate(const json &data) {
    try {
        validator.validate(data);
        return true;
    } catch (const std::exception &ex) {
        std::cerr << "Entity validation failed: " << ex.what() << std::endl;
        return false;
    }
}

unsigned int Entity::generate(const json &data) {
    if (validate(data)) {
        entities[id++] = data;
        return id - 1;
    }
    return 0;
}

void Entity::destroy(unsigned int id) {
    if (entities.find(id) != entities.end())
        entities.erase(id);
}