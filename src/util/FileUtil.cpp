//
// Created by Philip on 3/2/2020.
//

#include "FileUtil.h"

#include <iostream>
#include <fstream>
#include <sstream>


char* FileUtil::readResourceFile(const std::string &resourcePath) {
    std::ifstream resourceStream("../res/" + resourcePath, std::ifstream::ate);
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
    std::cout << "Error opening shader at res/" << resourcePath << std::endl;
    return nullptr;
}


json FileUtil::readJsonFile(const std::string &jsonPath) {
    return json::parse(std::ifstream("../res/" + jsonPath));
}

void FileUtil::writeJsonFile(const std::string &jsonPath, const json &data) {
    std::ofstream file;
    file.open("../res/" + jsonPath, std::ofstream::out);
    file << data;
    file.close();
}