//
// Created by Philip on 7/14/2020.
//

#include "MeshUtil.h"
#include "MathUtil.h"

Mesh::Ptr MeshUtil::generate_bezier_mesh(const std::vector<glm::vec3> &hull, double stepSize, glm::vec4 color) {
    auto curve = MathUtil::generate_bezier_curve(hull, stepSize);
    auto mesh = std::make_shared<Mesh>();
    for (int index = 0; index < curve.size(); index++) {
        // make all points on curve red
        mesh->vertices.emplace_back(curve[index].x, -curve[index].y, curve[index].z);
        mesh->colors.push_back(color);
        mesh->indices.push_back(index);
    }
    mesh->set_draw_mode(GL_LINE_STRIP);
    mesh->buffer();

    return mesh;
}

Mesh::Ptr MeshUtil::generate_line_mesh(const std::vector<glm::vec3> &points, glm::vec4 color) {
    auto mesh = std::make_shared<Mesh>();
    for (int index = 0; index < points.size(); index++) {
        // make all points on line red
        mesh->vertices.emplace_back(points[index].x, -points[index].y, points[index].z);
        mesh->colors.push_back(color);
        mesh->indices.push_back(index);
    }
    mesh->set_draw_mode(GL_LINE_STRIP);
    mesh->buffer();

    return mesh;
}

Mesh::Ptr MeshUtil::generate_box_mesh_triangles(int width, int height, int length, glm::vec4 color) {
    auto verts = MathUtil::generate_box(width, height, length);
    std::vector<unsigned int> indices = {
            1, 0, 2,
            2, 0, 3,

            4, 5, 6,
            6, 7, 4,

            0, 4, 7,
            7, 3, 0,

            6, 5, 1,
            2, 6, 1,

            4, 0, 5,
            5, 0, 1,

            6, 2, 7,
            7, 2, 3,
    };

    auto mesh = std::make_shared<Mesh>();
    for (auto vert: verts) {
        mesh->vertices.push_back(vert);
        mesh->colors.push_back(color);
    }
    for(auto index: indices)
        mesh->indices.push_back(index);
    mesh->set_draw_mode(GL_TRIANGLES);
    mesh->buffer();

    return mesh;
}

Mesh::Ptr MeshUtil::generate_box_mesh_lines(int width, int height, int length, glm::vec4 color) {
    auto verts = MathUtil::generate_box(width, height, length);
    std::vector<unsigned int> indices = {
            0, 1,
            1, 2,
            2, 3,
            3, 0,

            4, 5,
            5, 6,
            6, 7,
            7, 4,

            0, 4,
            1, 5,
            2, 6,
            3, 7
    };

    auto mesh = std::make_shared<Mesh>();
    for (auto vert: verts) {
        mesh->vertices.push_back(vert);
        mesh->colors.push_back(color);
    }
    for(auto index: indices)
        mesh->indices.push_back(index);
    mesh->set_draw_mode(GL_LINES);
    mesh->buffer();

    return mesh;
}

Mesh::Ptr MeshUtil::generate_quad_mesh(int width, int height, glm::vec4 color) {
    std::vector<glm::vec3> verts{
        {0,0, 0},
        {width, 0, 0},
        {width, 0, height},
        {0, 0, height}
    };
    std::vector<unsigned int> indices{
            1, 0, 2,
            2, 0, 3,
    };
    auto mesh = std::make_shared<Mesh>();
    for (auto vert: verts) {
        mesh->vertices.push_back(vert);
        mesh->colors.push_back(color);
    }
    for(auto index: indices)
        mesh->indices.push_back(index);
    mesh->set_draw_mode(GL_TRIANGLES);
    mesh->buffer();

    return mesh;
}
