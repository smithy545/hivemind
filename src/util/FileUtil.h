//
// Created by Philip on 3/2/2020.
//

#ifndef SOCIETY_FILEUTIL_H
#define SOCIETY_FILEUTIL_H

#include <nlohmann/json.hpp>
#include <string>


using json = nlohmann::json;

class FileUtil {
public:
    static const std::string RESOURCE_PREFIX;

    static char *readResourceFile(const std::string &resourcePath);

    static json readJsonFile(const std::string &jsonPath);

    static void writeJsonFile(const std::string &jsonPath, const json &data);

private:
    static std::string resource(std::string relativePath);
};


#endif //SOCIETY_FILEUTIL_H
