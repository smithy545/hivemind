//
// Created by Philip on 3/2/2020.
//

#ifndef SOCIETY_FILEUTIL_H
#define SOCIETY_FILEUTIL_H

#include <nlohmann/json.hpp>
#include <string>
#include <tinyxml.h>

using json = nlohmann::json;

class FileUtil {
public:
    static const std::string RESOURCE_PREFIX;
    static const std::string JSON_PREFIX;

    static char *readResourceFile(const std::string &resourcePath);

    static json readJsonFile(const std::string &jsonPath, bool prefixPath = true);

    static TiXmlDocument readXmlFile(const std::string &xmlPath);

    static void writeJsonFile(const std::string &jsonPath, const json &data);

private:
    static std::string resource(std::string relativePath);
};


#endif //SOCIETY_FILEUTIL_H
