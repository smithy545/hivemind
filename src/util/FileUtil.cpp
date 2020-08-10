//
// Created by Philip on 3/2/2020.
//

#include "FileUtil.h"

#include <iostream>
#include <fmt/format.h>
#include <fstream>


const std::string FileUtil::RESOURCE_PREFIX = "../res/{0}";
const std::string FileUtil::JSON_PREFIX = "json/{0}";

std::string FileUtil::resource(std::string relative_path) {
    return fmt::format(RESOURCE_PREFIX, relative_path);
}

char *FileUtil::read_resource_file(const std::string &resource_path) {
    std::ifstream resourceStream(resource(resource_path), std::ifstream::ate);
    if (resourceStream) {
        // get file length (ifstream::ate flag puts cursor at end of file)
        int length = resourceStream.tellg();
        resourceStream.seekg(0, std::ios_base::beg);

        // store in buffer
        char *buf = new char[length];
        int count = 0;
        while (resourceStream.read(buf + count, length - count) || resourceStream.gcount() != 0) {
            count += resourceStream.gcount();
        }
        resourceStream.close();

        // null terminate at actual read file count
        buf[count] = '\0';

        // MUST BE DELETED WHEN FINISHED WITH USE. TODO: Find safer (no memleaks) way to read file
        return buf;
    }

    // open failed for some reason
    std::string message = fmt::format("Can't read file at {0}", resource(resource_path));
    throw std::exception(message.c_str());
}


json FileUtil::read_json_file(const std::string &json_path, const json &schema, bool prefix_path) {
    std::string path = prefix_path ? resource(fmt::format(JSON_PREFIX, json_path)) : resource(json_path);
    std::ifstream file(path);
    if (file.good()) {
        auto data = json::parse(file);
        if (schema != nullptr) {
            json_validator validator;
            try {
                validator.set_root_schema(schema);
            } catch (std::exception e) {
                std::cerr << "Schema error: " << e.what() << std::endl;
            }
            try {
                validator.validate(data);
            } catch (std::exception e) {
                std::cerr << "Validation error: " << e.what() << std::endl;
            }
        }
        return data;
    }
    std::string message = fmt::format("Can't read json file at {0}", resource(json_path));
    throw std::exception(message.c_str());
}

void FileUtil::write_json_file(const std::string &json_path, const json &data) {
    std::ofstream file;
    file.open(resource(json_path), std::ofstream::out);
    file << data;
    file.close();
}
