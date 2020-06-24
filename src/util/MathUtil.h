//
// Created by Philip on 5/11/2020.
//

#ifndef SOCIETY_MATHUTIL_H
#define SOCIETY_MATHUTIL_H

#include <glm/glm.hpp>
#include <vector>

class MathUtil {
public:
    static int binomial_coeff(int n, int k);

    // 2-D utils
    static std::vector<glm::vec2> generate_bezier_curve(std::vector<glm::vec2> control_points, double step_size);

    // 3-D utils
    static std::vector<glm::vec3> generate_bezier_curve(std::vector<glm::vec3> control_points, double step_size);
    static std::vector<glm::vec3> generate_sphere(double radius, double phi_step, double theta_step);
    static std::vector<glm::vec3> generate_cylinder(double radius, double length, double length_step, double phi_step);
    static std::vector<glm::vec3> generate_box(double width, double height, double length);
    // TODO: static std::vector<glm::vec3> generate_ovaloid();

    // N-D utils
    static std::vector<float> generate_bezier_curve(std::vector<float> control_points, double step_size, int dimension);
    // TODO: static int* generate_binomial_matrix(int n, int k);
private:
    static std::vector<int *> generated_binomial_coeffs;
    static int max_generated_degree;

    // generate bezier curve for given control points

    // via polynomial function
    static std::vector<float> bezier_polynomial(std::vector<float> points, double step_size, int dimension);
    // geometrically
    static std::vector<float> bezier_deCasteljau(std::vector<float> points, double step_size, int dimension);
    static std::vector<float> deCasteljau_kernel(std::vector<float> points, double t, int dimension);
    // via matrix operations
    // TODO: static std::vector<float> bezier_matrix(std::vector<float> control_points, double step_size, int dimension);
};


#endif //SOCIETY_MATHUTIL_H
