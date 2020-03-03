//
// Created by Philip on 3/2/2020.
//

#ifndef HIVEMIND_FILEUTIL_H
#define HIVEMIND_FILEUTIL_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


class FileUtil {
public:
    static char* readResourceFile(const std::string& resourcePath);

    static json readJsonFile(const std::string& jsonPath);
};


#endif //HIVEMIND_FILEUTIL_H
