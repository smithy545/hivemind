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
    static std::vector<glm::vec3> generateBezierCurve(std::vector<glm::vec3> controlPoints, double stepSize);
    static std::vector<glm::vec3> generateSphere(double radius, double phiStep, double thetaStep);
    static std::vector<glm::vec3> generateCylinder(double radius, double length, double lengthStep, double phiStep);
    static std::vector<glm::vec3> generateBox(double width, double height, double length);
    // TODO: static std::vector<glm::vec3> generateOvaloid();

    // N-D utils
    static std::vector<float> generateBezierCurve(std::vector<float> controlPoints, double stepSize, int dimension);
    // TODO: static int* generateBinomialMatrix(int n, int k);
private:
    static std::vector<int *> generatedBinomialCoeffs;
    static int maxGeneratedDegree;

    // generate bezier curve for given control points

    // via polynomial function
    static std::vector<float> bezierPolynomial(std::vector<float> points, double stepSize, int dimension);
    // geometrically
    static std::vector<float> bezierDeCasteljau(std::vector<float> points, double stepSize, int dimension);
    static std::vector<float> deCasteljauKernel(std::vector<float> points, double t, int dimension);
    // via matrix operations
    static std::vector<float> bezierMatrix(std::vector<float> controlPoints, double stepSize, int dimension);
};


#endif //SOCIETY_MATHUTIL_H
