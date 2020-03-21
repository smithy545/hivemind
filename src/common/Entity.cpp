//
// Created by Philip on 3/21/2020.
//

#include "Entity.h"

#include <iostream>
#include <util/FileUtil.h>



Entity::Entity(const json &schema) : schema(schema) {
    try {
        validator.set_root_schema(schema);
    } catch (const std::exception &ex) {
        std::cerr << "Schema setup failed: " << ex.what() << std::endl;
    }
}

bool Entity::validate() {
    try {
        // pack and validate
        validator.validate(pack());
        return true;
    } catch (const std::exception &ex) {
        std::cerr << "Entity validation failed: " << ex.what() << std::endl;
        return false;
    }
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

bool Entity::storeToFile(const std::string &filePath) {
    json data = pack();
    if (!validate(data))
        return false;
    FileUtil::writeJsonFile(filePath, data);
    return true;
}

bool Entity::loadFromFile(const std::string &filePath) {
    return unpack(FileUtil::readJsonFile(filePath));
}
