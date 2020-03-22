//
// Created by Philip on 3/2/2020.
//

#ifndef SOCIETY_FILEUTIL_H
#define SOCIETY_FILEUTIL_H

#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;


class FileUtil {
public:
    static char *readResourceFile(const std::string &resourcePath);

    static json readJsonFile(const std::string &jsonPath);

    static void writeJsonFile(const std::string &jsonPath, const json &data);
};


#endif //SOCIETY_FILEUTIL_H
