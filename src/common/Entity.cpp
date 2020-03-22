//
// Created by Philip on 3/21/2020.
//

#include "Entity.h"

#include <iostream>
#include <util/FileUtil.h>

using nlohmann::json_schema::json_validator;


Entity::Entity(json schema) : schema(std::move(schema)) {}

bool Entity::validate() {
    json_validator validator;
    validator.set_root_schema(schema);

    try {
        // pack and validate
        validator.validate(pack());
        return true;
    } catch (const std::exception &ex) {
        std::cerr << "Entity validation failed: " << ex.what() << std::endl;
        return false;
    }
}

bool Entity::storeToFile(const std::string &filePath) {
    FileUtil::writeJsonFile(filePath, pack());
    return true;
}

bool Entity::loadFromFile(const std::string &filePath) {
    return unpack(FileUtil::readJsonFile(filePath));
}