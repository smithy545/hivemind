//
// Created by Philip on 5/11/2020.
//

#ifndef SOCIETY_MATHUTIL_H
#define SOCIETY_MATHUTIL_H

#include <glm/glm.hpp>
#include <vector>

class MathUtil {
public:
    static int binomialCoeff(int n, int k);

    // 2-D utils
    static std::vector<glm::vec2> generateBezierCurve(std::vector<glm::vec2> controlPoints, double stepSize);

    // 3-D utils
    static std::vector<glm::vec3> generateSphere(double radius, double phiStep, double thetaStep);
    static std::vector<glm::vec3> generateCylinder(double radius, double length, double lengthStep, double phiStep);
    static std::vector<glm::vec3> generateBox(double width, double height, double length);
    // TODO: static std::vector<glm::vec3> generateOvaloid();

    // N-D utils
    // TODO: static int* generateBinomialMatrix(int n, int k);
private:
    static std::vector<int *> generatedBinomialCoeffs;
    static int maxGeneratedDegree;

    // generate bezier curve for given control points
    static std::vector<glm::vec2> bezierPolynomial(std::vector<glm::vec2> points, double stepSize);    // via polynomial function
    static std::vector<glm::vec2> bezierDeCasteljau(std::vector<glm::vec2> points, double stepSize);   // geometrically
    static std::vector<glm::vec2> bezierMatrix(std::vector<glm::vec2> controlPoints, double stepSize); // via matrix operations
    static glm::vec2 deCasteljauKernel(std::vector<glm::vec2> points, double t);

};


#endif //SOCIETY_MATHUTIL_H
