//
// Created by Philip on 3/1/2020.
//

#include "Renderer.h"

#include <iostream>
#include <fmt/format.h>

#include "util/FileUtil.h"
#include "util/MathUtil.h"
#include "util/RenderUtil.h"


GLFWwindow* Renderer::init(const std::string& config_path) {
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
    //glEnable(GL_CULL_FACE);

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

    if(set_shader(DEFAULT_SHADER_NAME))
        std::cout << "Shader set to default: " << DEFAULT_SHADER_NAME << std::endl;
    else
        std::cerr << "Error setting default shader: " << DEFAULT_SHADER_NAME << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // disable cursor to enable automatic recentering
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // clear background to black
    glClearColor(1.0f,1.0f, 1.0f, 1.0f);

    return window;
}

void Renderer::cleanup() {
    // clear loaded textures
    loaded_textures.clear();

    // clear loaded shaders
    for (auto &shaderProgram : loaded_shaders) {
        glDeleteProgram(shaderProgram.second);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources
    glfwTerminate();
}

void Renderer::render(const Camera::Ptr& camera, const Map::Ptr& map) {
    glUseProgram(current_shader_program);
    auto vp_matrix = camera->get_view_projection_matrix();
    auto mesh = map->get_mesh();
    if(mesh != nullptr) {
        // bind vertex array object
        glBindVertexArray(mesh->get_vertex_array_id());

        // store in shader uniform
        glUniformMatrix4fv(vp_uniform, 1, GL_FALSE, &vp_matrix[0][0]);
        // draw instances
        glDrawElements(mesh->get_draw_mode(), mesh->get_num_indices(), GL_UNSIGNED_INT, 0);
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
        vp_uniform = glGetUniformLocation(current_shader_program, "VP");
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


void Renderer::load_texture(const std::string &name, const std::string &texture_path) {
    int w, h;
    loaded_textures[name] = RenderUtil::load_texture(texture_path, w, h);
}
