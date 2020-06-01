//
// Created by Philip on 5/11/2020.
//

#include "MathUtil.h"

#include <iostream>
#include <utility>

#define BEZIER_GEOMETRIC 1

std::vector<int *> MathUtil::generatedBinomialCoeffs;
int MathUtil::maxGeneratedDegree = 0;

int MathUtil::binomialCoeff(int n, int k) {
    while (n >= maxGeneratedDegree) {
        int s = maxGeneratedDegree;
        int *coeffs = new int[s + 1];
        coeffs[0] = 1;
        for (int i = 1, prev = s - 1; i < s; i++)
            coeffs[i] = generatedBinomialCoeffs[prev][i - 1] + generatedBinomialCoeffs[prev][i];
        coeffs[s] = 1;
        generatedBinomialCoeffs.push_back(coeffs);
        maxGeneratedDegree++;
    }

    return generatedBinomialCoeffs[n][k];
}

std::vector<glm::vec2> MathUtil::generateBezierCurve(std::vector<glm::vec2> controlPoints, double stepSize) {
    if (controlPoints.size() <= 2) {
        return controlPoints;
    }

#ifdef BEZIER_POLYNOMIAL
    return bezierPolynomial(std::move(controlPoints), stepSize);
#elif BEZIER_GEOMETRIC
    return bezierDeCasteljau(std::move(controlPoints), stepSize);
#else
    return bezierMatrix(std::move(controlPoints), stepSize);
#endif
}

std::vector<glm::vec2> MathUtil::bezierPolynomial(std::vector<glm::vec2> points, double stepSize) {
    // add first point to curve
    std::vector<glm::vec2> curve{points.front()};
    int n = points.size() - 1;
    double t = stepSize;
    while (t < 1.0) {
        double x{0}, y{0};
        double subT = 1.0 - t;
        for (int k = 0; k <= n; k++) {
            int subK = n - k;
            double coeff = MathUtil::binomialCoeff(n, k) * std::pow(subT, subK) * std::pow(t, k);
            // round to zero at threshold=0.001
            coeff = coeff > 0.001 ? coeff : 0;
            x += points[k].x * coeff;
            y += points[k].y * coeff;
        }

        curve.emplace_back(x, y);
        t += stepSize;
    }

    // add last point to curve
    curve.push_back(points.back());

    return curve;
}


std::vector<glm::vec2> MathUtil::bezierDeCasteljau(std::vector<glm::vec2> points, double stepSize) {
    // add first point to curve
    std::vector<glm::vec2> curve{points.front()};
    double t = stepSize;
    while (t < 1.0) {
        curve.push_back(deCasteljauKernel(points, t));
        t += stepSize;
    }

    return curve;
}

glm::vec2 MathUtil::deCasteljauKernel(std::vector<glm::vec2> points, double t) {
    if (points.size() <= 1)
        return points[0];

    std::vector<glm::vec2> curve;
    for (int i = 0; i < points.size() - 1; i++) {
        double x = (1 - t) * points[i].x + t * points[i + 1].x;
        double y = (1 - t) * points[i].y + t * points[i + 1].y;
        curve.emplace_back(x, y);
    }
    return deCasteljauKernel(curve, t);
}

std::vector<glm::vec2> MathUtil::bezierMatrix(std::vector<glm::vec2> points, double stepSize) {
    return std::vector<glm::vec2>();
}

std::vector<glm::vec3> MathUtil::generateSphere(double radius, double phiStep, double thetaStep) {
    auto surfacePoints = std::vector<glm::vec3>();
    for(double phi = 0.0; phi <= 0.5*3.14159265358979; phi += phiStep) {
        for(double theta = 0.0; theta < 3.14159265358979; theta += thetaStep) {
            surfacePoints.emplace_back(radius*glm::sin(theta)*glm::cos(phi), radius*glm::sin(theta)*glm::sin(phi), radius*glm::cos(theta));
        }
    }

    return surfacePoints;
}

std::vector<glm::vec3> MathUtil::generateCylinder(double radius, double length, double lengthStep, double phiStep) {
    auto surfacePoints = std::vector<glm::vec3>();
    for(double z = 0.0; z <= length; z += lengthStep) {
        for(double phi = 0.0; phi < 3.14159265358979; phi += phiStep) {
            surfacePoints.emplace_back(z*glm::cos(phi), z*glm::sin(phi), z);
        }
    }
    return {};
}

std::vector<glm::vec3> MathUtil::generateBox(double width, double height, double length) {
    return {
            {0, 0, 0},
            {width, 0, 0},
            {width, height, 0},
            {0, height, 0},
            {0, 0, length},
            {width, 0, length},
            {width, height, length},
            {0, height, length}
    };
}
