//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_JOINT_H
#define SOCIETY_JOINT_H

#include <utility>
#include <vector>

#include "macros.h"


class Appendage;

class Joint {
public:
    POINTERIZE(Joint);

    enum Muscle {
        CONVEX,
        REFLEX,
        BOTH
    };

    Joint(SP(Appendage) first, SP(Appendage) second);

    // pull joint muscle
    void pullConvex();
    void pullReflex();
private:
    SP(Appendage) first, second;
    std::vector<std::pair<double, double>> includedRegions;
    double triangulature = 0.1; // how triangle looking should the muscle be?
};


#endif //SOCIETY_JOINT_H
