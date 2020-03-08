//
// Created by Philip on 3/3/2020.
//

#ifndef SOCIETY_RECIPE_H
#define SOCIETY_RECIPE_H

#include <memory>
#include <vector>

#include "world/Prop.h"
#include "world/Structure.h"


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

    int turnsToProduce; // if 0 production is instant
    Structure::Ptr requiredStructure{nullptr}; // if not present no structure is required
    std::vector<Prop::Ptr> inputs;
    Prop::Ptr output;
};


#endif //SOCIETY_RECIPE_H
