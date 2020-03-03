//
// Created by Philip on 3/3/2020.
//

#ifndef SOCIETY_RECIPE_H
#define SOCIETY_RECIPE_H

#include <vector>

#include "Prop.h"


class Recipe {
    std::vector<Prop::Ptr> inputs;
    Prop::Ptr output;
};


#endif //SOCIETY_RECIPE_H
