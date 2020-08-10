//
// Created by Philip on 3/2/2020.
//

#ifndef SOCIETY_FILEUTIL_H
#define SOCIETY_FILEUTIL_H

#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>
#include <string>


using json = nlohmann::json;
using namespace nlohmann::json_schema;

class FileUtil {
public:
    static const std::string RESOURCE_PREFIX;
    static const std::string JSON_PREFIX;

    static char *read_resource_file(const std::string &resource_path);

    static json read_json_file(const std::string &json_path, const json &schema = nullptr, bool prefix_path = true);

    static void write_json_file(const std::string &json_path, const json &data);

private:
    static std::string resource(std::string relative_path);
};


#endif //SOCIETY_FILEUTIL_H
