//
// Created by Philip on 5/11/2020.
//

#include "MathUtil.h"

#include <utility>


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

    std::vector<float> points;
    for(auto p: controlPoints) {
        points.push_back(p.x);
        points.push_back(p.y);
    }

    std::vector<float> curve = generateBezierCurve(points, stepSize, 2);

    std::vector<glm::vec2> returnPoints;
    for(int i = 0; i < curve.size() - 1; i += 2)
        returnPoints.emplace_back(curve[i], curve[i + 1]);

    return returnPoints;
}

std::vector<glm::vec3> MathUtil::generateBezierCurve(std::vector<glm::vec3> controlPoints, double stepSize) {
    if (controlPoints.size() <= 2) {
        return controlPoints;
    }

    auto points = std::vector<float>();
    for(auto p: controlPoints) {
        points.push_back(p.x);
        points.push_back(p.y);
        points.push_back(p.z);
    }

    std::vector<float> curve = generateBezierCurve(points, stepSize, 3);

    std::vector<glm::vec3> returnPoints;
    for(int i = 0; i < curve.size() - 2; i += 3)
        returnPoints.emplace_back(curve[i], curve[i + 1], curve[i + 2]);

    return returnPoints;
}

std::vector<float> MathUtil::generateBezierCurve(std::vector<float> controlPoints, double stepSize, int dimension) {
    if (controlPoints.size() <= 2) {
        return controlPoints;
    }

#ifdef BEZIER_POLYNOMIAL
    return bezierPolynomial(std::move(controlPoints), stepSize, dimension);
#else
    return bezierDeCasteljau(std::move(controlPoints), stepSize, dimension);
#endif
}

std::vector<float> MathUtil::bezierPolynomial(std::vector<float> points, double stepSize, int dimension) {
    // add first point to curve
    std::vector<float> curve;
    curve.insert(std::end(curve), std::begin(points), std::begin(points) + dimension);
    int n = points.size()/dimension - 1;
    double t = stepSize;

    while (t < 1.0) {
        // setup output vector
        std::vector<float> v;
        v.reserve(dimension);
        for(int i = 0; i < dimension; i++)
            v.push_back(0);

        double subT = 1.0 - t;
        for (int k = 0; k <= n; k++) {
            int subK = n - k;
            double coeff = MathUtil::binomialCoeff(n, k) * std::pow(subT, subK) * std::pow(t, k);
            // round to zero at threshold=0.001
            coeff = coeff > 0.001 ? coeff : 0;
            for(int i = 0; i < dimension; i++)
                v[i] += points[k*dimension + i] * coeff;
        }

        curve.insert(std::end(curve), std::begin(v), std::end(v));
        t += stepSize;
    }

    // add last point to curve
    curve.insert(std::end(curve), std::end(points) - dimension, std::end(points));

    return curve;
}


std::vector<float> MathUtil::bezierDeCasteljau(std::vector<float> points, double stepSize, int dimension) {
    // add first point to curve
    std::vector<float> curve;
    curve.insert(std::end(curve), std::begin(points), std::begin(points) + dimension);
    double t = stepSize;
    while (t < 1.0) {
        auto subCurve = deCasteljauKernel(points, t, dimension);
        curve.insert(std::end(curve), std::begin(subCurve), std::end(subCurve));
        t += stepSize;
    }

    return curve;
}

std::vector<float> MathUtil::deCasteljauKernel(std::vector<float> points, double t, int dimension) {
    if (points.size() <= dimension)
        return points;

    std::vector<float> curve;
    for (int i = 0; i < points.size() - dimension; i += dimension) {
        for(int j = 0; j < dimension; j++)
            curve.push_back((1 - t) * points[i + j] + t * points[i + dimension + j]);
    }
    return deCasteljauKernel(curve, t, dimension);
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
    return surfacePoints;
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
