//
// Created by Philip on 5/11/2020.
//

#ifndef CELL_MATHUTIL_H
#define CELL_MATHUTIL_H

#include <glm/glm.hpp>
#include <vector>

class MathUtil {
public:
    static int binomialCoeff(int n, int k);

    static std::vector<glm::vec2> generateBezierCurve(std::vector<glm::vec2> controlPoints, double stepSize);

    // TODO: static int* binomialMatrix(int n, int k);
private:
    static std::vector<int *> generatedBinomialCoeffs;
    static int maxGeneratedDegree;

    // generate bezier curve for given control points via polynomial function
    static std::vector<glm::vec2> bezierNaive(std::vector<glm::vec2> controlPoints, double stepSize);
    // TODO: std::vector<glm::vec2> bezierDeCasteljau() // generate geometrically
    // TODO: std::vector<glm::vec2> bezierMatrix()      // generate via matrix operations
};


#endif //CELL_MATHUTIL_H
