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
    return bezierNaive(std::move(controlPoints), stepSize);
}

std::vector<glm::vec2> MathUtil::bezierNaive(std::vector<glm::vec2> controlPoints, double stepSize) {
    std::vector<glm::vec2> curvePoints;
    int n = controlPoints.size() - 1;
    double t = 0.0;
    while (t <= 1.0) {
        double x{0}, y{0};
        double subT = 1.0 - t;
        for (int k = 0; k <= n; k++) {
            int subK = n - k;
            float coeff = MathUtil::binomialCoeff(n, k) * std::pow(subT, subK) * std::pow(t, k);
            // round to zero at threshold=0.001
            coeff = coeff > 0.001 ? coeff : 0;
            x += controlPoints[k].x * coeff;
            y += controlPoints[k].y * coeff;
        }

        curvePoints.emplace_back(x, y);
        t += stepSize;
    }

    return curvePoints;
}
