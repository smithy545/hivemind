//
// Created by Philip on 7/14/2020.
//

#ifndef SOCIETY_MESHUTIL_H
#define SOCIETY_MESHUTIL_H

#include "render/Mesh.h"


class MeshUtil {
public:
    static Mesh::Ptr generate_bezier_mesh(const std::vector<glm::vec3> &hull, double stepSize, glm::vec4 color);

    static Mesh::Ptr generate_line_mesh(const std::vector<glm::vec3> &points, glm::vec4 color);

    static Mesh::Ptr generate_box_mesh_triangles(int width, int height, int length, glm::vec4 color);

    static Mesh::Ptr generate_box_mesh_lines(int width, int height, int length, glm::vec4 color);

    static Mesh::Ptr generate_quad_mesh(int width, int height, glm::vec4 color);
};


#endif //SOCIETY_MESHUTIL_H
