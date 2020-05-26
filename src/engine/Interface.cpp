//
// Created by Philip on 2/25/2020.
//

#include "Interface.h"

#include <nlohmann/json.hpp>

#include "util/FileUtil.h"


Interface::Interface(const std::string &configPath) {
    // read config
    auto configSchema = json::parse(R"({
    "title": "User interface initialization config",
    "type": "object",
    "properties": {},
    "required": []
})");
    auto config = FileUtil::readJsonFile(configPath, configSchema);
}

void Interface::update(const State::Ptr &state) {
    if (state->getMouseScroll() > 0) {
        state->getCamera()->zoomIn();
    } else if (state->getMouseScroll() < 0) {
        state->getCamera()->zoomOut();
    }
    if (state->getKey(GLFW_KEY_LEFT)) {
        state->getCamera()->panLeft();
    }
    if (state->getKey(GLFW_KEY_RIGHT)) {
        state->getCamera()->panRight();
    }
    if (state->getKey(GLFW_KEY_UP)) {
        state->getCamera()->panUp();
    }
    if (state->getKey(GLFW_KEY_DOWN)) {
        state->getCamera()->panDown();
    }

    double mx = state->getMouseX();
    double my = state->getMouseY();
}
