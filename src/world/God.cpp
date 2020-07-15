//
// Created by Philip on 7/8/2020.
//

#include "God.h"


God::God() {
    // let there be light
}

void God::update() {
    for(const auto& actor: actors) {
        actor->update();
    }
}

void God::generate_town() {

}

void God::generate_person() {

}

void God::generate_house() {

}
