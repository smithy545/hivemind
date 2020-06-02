//
// Created by Philip on 6/1/2020.
//

#include "Joint.h"

#include <utility>


Joint::Joint(SP(Appendage) first, SP(Appendage) second) : first(std::move(first)), second(std::move(second)) {}

void Joint::pullConvex() {

}

void Joint::pullReflex() {

}
