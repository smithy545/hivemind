//
// Created by Philip on 3/3/2020.
//

#ifndef SOCIETY_RECIPE_H
#define SOCIETY_RECIPE_H

#include <memory>
#include <vector>

#include "Prop.h"
#include "Structure.h"


// Recipe defining process for generating certain prop
class Recipe {
public:
    typedef std::shared_ptr<Recipe> Ptr;
private:
    // if active a human must be present for entire production
    enum ProductionType {
        ACTIVE,
        PASSIVE
    };

    int turnsToProduce;
    Structure::Ptr requiredStructure{nullptr};
    std::vector<Prop::Ptr> inputs;
    Prop::Ptr output;
};


#endif //SOCIETY_RECIPE_H
