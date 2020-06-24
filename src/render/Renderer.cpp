//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <iostream>
#include <fmt/format.h>
#include <glm/ext.hpp>

#include "util/FileUtil.h"
#include "util/MathUtil.h"
#include "util/RenderUtil.h"
#include "util/StringUtil.h"


GLFWwindow *Renderer::init(const std::string& config_path) {
    auto config = FileUtil::read_json_file(config_path, CONFIG_SCHEMA);
    _width = config[WIDTH_KEY];
    _height = config[HEIGHT_KEY];

    // Initialise GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(_width, _height, "SOCIETY", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // enable srgb
    glEnable(GL_FRAMEBUFFER_SRGB);

    // cull triangles facing away from camera
    glEnable(GL_CULL_FACE);

    // enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // shaders
    for (const auto &shader: config[SHADERS_KEY].items()) {
        std::cout << fmt::format("Loading shader \"{0}\" from {1} {2} ", shader.key(), shader.value()[0],
                                 shader.value()[1])
                  << std::endl;
        load_shader(shader.key(), shader.value()[0], shader.value()[1]);
    }

    // image textures
    for (const auto &tex: config[TEXTURES_KEY].items()) {
        std::cout << fmt::format("Loading texture \"{0}\" from {1}", tex.key(), tex.value()) << std::endl;
        load_texture(tex.key(), tex.value());
    }

    // tilesheet textures
    for (const auto &tilesheet: config[TILESHEETS_KEY]) {
        std::cout << fmt::format("Loading tilesheet from {0}", tilesheet) << std::endl;
        load_tilesheet(tilesheet);
    }

    // sprites
    for (const auto &sprite: config[SPRITESHEETS_KEY]) {
        std::cout << fmt::format("Loading sprite from {0}", sprite) << std::endl;
        load_sprite(sprite);
    }

    set_shader(DEFAULT_SHADER_NAME);

    return window;
}

void Renderer::cleanup() {
    // clear loaded meshes
    loaded_textures.clear();

    // clear loaded shaders
    for (auto &shaderProgram : loaded_shaders) {
        glDeleteProgram(shaderProgram.second);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources
    glfwTerminate();
}

void Renderer::render(const RenderNode::Ptr &tree_head, const Camera::Ptr& camera) {
    glUseProgram(current_shader_program);
    auto vp_matrix = camera->get_view_projection_matrix();
    auto node = tree_head;
    while (node != nullptr) {
        auto entity = node->get_entity();
        if(set_shader(node->get_shader_name()) && entity!= nullptr) {
            glBindVertexArray(entity->get_vertex_array_id());
            auto tex = entity->get_texture();
            if (!tex.empty() && loaded_textures.find(tex) != loaded_textures.end()) {
                GLuint texId = loaded_textures[tex];
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texId);
            }

            for (const auto &body: node->get_bodies()) {
                // translate to world position
                glm::mat4 model_matrix = glm::translate(glm::mat4(1), body->get_origin());
                glm::mat4 mvp_matrix = vp_matrix * model_matrix;
                glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, &mvp_matrix[0][0]);
                glDrawElements(entity->get_draw_mode(),
                         entity->get_num_indices() * sizeof(unsigned int),
                               GL_UNSIGNED_INT, nullptr);
            }
        }
        node = std::dynamic_pointer_cast<RenderNode>(node->get_next());
    }
}

void Renderer::resize(int width, int height) {
    _width = width;
    _height = height;
}

bool Renderer::set_shader(const std::string &name) {
    if(name == current_shader_name)
        return true;
    else if (loaded_shaders.find(name) != loaded_shaders.end()) {
        current_shader_name = name;
        current_shader_program = loaded_shaders[name];
        glUseProgram(current_shader_program);
        mvp_uniform = glGetUniformLocation(current_shader_program, "MVP");
        tex_uniform = glGetUniformLocation(current_shader_program, "tex");
        glUniform1i(tex_uniform, 0);
        return true;
    }
    std::cerr << "No shader found with name " << name << std::endl;
    return false;
}

void Renderer::load_shader(const std::string &name, const std::string &vertex_shader_path,
                           const std::string &fragment_shader_path) {
    loaded_shaders[name] = RenderUtil::load_shader_program(vertex_shader_path, fragment_shader_path);
}

void Renderer::load_sprite(const std::string &path) {
    auto spriteData = FileUtil::read_json_file(fmt::format("spritesheets/{}", path), SPRITE_SCHEMA);
    std::string tex = spriteData[TEXTURE_KEY];
    Sprite::Ptr sprite = std::make_shared<Sprite>(tex);
    float spriteWidth = spriteData[WIDTH_KEY];
    float spriteHeight = spriteData[HEIGHT_KEY];
    std::string name = spriteData[NAME_KEY];

    // bottom left
    sprite->get_vertices().emplace_back(0, 0);
    sprite->get_uvs().emplace_back(0, 0);

    // bottom right
    sprite->get_vertices().emplace_back(spriteWidth, 0);
    sprite->get_uvs().emplace_back(1, 0);

    // top right
    sprite->get_vertices().emplace_back(spriteWidth, spriteHeight);
    sprite->get_uvs().emplace_back(1, -1);

    // top left
    sprite->get_vertices().emplace_back(0, spriteHeight);
    sprite->get_uvs().emplace_back(0, -1);

    // indices
    sprite->get_indices().push_back(0);
    sprite->get_indices().push_back(2);
    sprite->get_indices().push_back(3);

    sprite->get_indices().push_back(1);
    sprite->get_indices().push_back(2);
    sprite->get_indices().push_back(0);

    loaded_sprites[name] = sprite;
}

void Renderer::load_texture(const std::string &name, const std::string &texture_path) {
    int w, h;
    loaded_textures[name] = RenderUtil::load_texture(texture_path, w, h);
}

void Renderer::load_tilesheet(const std::string &path) {
    auto tilesheet = FileUtil::read_json_file(fmt::format("tilesheets/{}", path), TILESHEET_SCHEMA);

    std::string name = tilesheet[NAME_KEY];
    int sheet_tilesize = tilesheet[TILESIZE_KEY];
    int w, h;
    loaded_textures[name] = RenderUtil::load_texture(tilesheet[TEXTURE_KEY], w, h);
    loaded_textures[name] = RenderUtil::load_texture(tilesheet[TEXTURE_KEY], w, h);

    int i = 0;
    float uStep = sheet_tilesize / (1.0 * w);
    float vStep = sheet_tilesize / (1.0 * h);
    for (float v = 0; v >= -1.0; v -= vStep) {
        for (float u = 0; u < 1.0; u += uStep) {
            Sprite::Ptr sprite = std::make_shared<Sprite>(name);

            // bottom left
            sprite->get_vertices().emplace_back(0, 0);
            sprite->get_uvs().emplace_back(u, v);

            // bottom right
            sprite->get_vertices().emplace_back(sheet_tilesize, 0);
            sprite->get_uvs().emplace_back(u + uStep, v);

            // top right
            sprite->get_vertices().emplace_back(sheet_tilesize, sheet_tilesize);
            sprite->get_uvs().emplace_back(u + uStep, v - vStep);

            // top left
            sprite->get_vertices().emplace_back(0, sheet_tilesize);
            sprite->get_uvs().emplace_back(u, v - vStep);

            // indices
            sprite->get_indices().push_back(0);
            sprite->get_indices().push_back(2);
            sprite->get_indices().push_back(3);

            sprite->get_indices().push_back(1);
            sprite->get_indices().push_back(2);
            sprite->get_indices().push_back(0);

            loaded_sprites[fmt::format("{0}_{1}", name, i)] = sprite;
            i++;
        }
    }

    // setup sprites
    json_validator validator;
    try {
        validator.set_root_schema(SPRITE_SCHEMA);
    } catch (std::exception &e) {
        std::cerr << "Schema error: " << e.what() << std::endl;
        return;
    }
    for (const auto& spriteInfo: tilesheet[SPRITES_KEY]) {
        try {
            validator.validate(spriteInfo);
        } catch(std::exception &e) {
            std::cerr << "Validation error: " << e.what() << std::endl;
            continue;
        }

        if(loaded_sprites.find(spriteInfo[TEXTURE_KEY]) != loaded_sprites.end()) {
            // replace tile name with sprite name
            loaded_sprites[spriteInfo[NAME_KEY]] = loaded_sprites[spriteInfo[TEXTURE_KEY]];
            loaded_sprites.erase(spriteInfo[TEXTURE_KEY]);
        }
    }
}

Mesh::Ptr Renderer::generate_bezier_mesh(const std::vector<glm::vec3> &hull, double stepSize, glm::vec4 color) {
    auto curve = MathUtil::generate_bezier_curve(hull, stepSize);
    auto mesh = std::make_shared<Mesh>();
    for (int index = 0; index < curve.size(); index++) {
        // make all points on curve red
        mesh->get_vertices().emplace_back(curve[index].x, -curve[index].y, curve[index].z);
        mesh->get_colors().push_back(color);
        mesh->get_indices().push_back(index);
    }
    mesh->set_draw_mode(GL_LINE_STRIP);
    mesh->bufferVertices();
    mesh->bufferColors();
    mesh->bufferIndices();

    return mesh;
}

Mesh::Ptr Renderer::generate_line_mesh(const std::vector<glm::vec3> &points, glm::vec4 color) {
    auto mesh = std::make_shared<Mesh>();
    for (int index = 0; index < points.size(); index++) {
        // make all points on line red
        mesh->get_vertices().emplace_back(points[index].x, -points[index].y, points[index].z);
        mesh->get_colors().push_back(color);
        mesh->get_indices().push_back(index);
    }
    mesh->set_draw_mode(GL_LINE_STRIP);
    mesh->bufferVertices();
    mesh->bufferColors();
    mesh->bufferIndices();

    return mesh;
}

Mesh::Ptr Renderer::generate_box_mesh_triangles(int width, int height, int length, glm::vec4 color) {
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
        mesh->get_vertices().push_back(vert);
        mesh->get_colors().push_back(color);
    }
    for(auto index: indices)
        mesh->get_indices().push_back(index);
    mesh->set_draw_mode(GL_TRIANGLES);
    mesh->bufferVertices();
    mesh->bufferColors();
    mesh->bufferIndices();

    return mesh;
}

Mesh::Ptr Renderer::generate_box_mesh_lines(int width, int height, int length, glm::vec4 color) {
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
        mesh->get_vertices().push_back(vert);
        mesh->get_colors().push_back(color);
    }
    for(auto index: indices)
        mesh->get_indices().push_back(index);
    mesh->set_draw_mode(GL_LINES);
    mesh->bufferVertices();
    mesh->bufferColors();
    mesh->bufferIndices();

    return mesh;
}
