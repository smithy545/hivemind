//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_RENDERER_H
#define SOCIETY_RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "Camera.h"
#include "macros.h"
#include "pathing/GridMap.h"
#include "RenderNode.h"


using namespace nlohmann;

class Renderer {
public:
    // lifecycle methods
    GLFWwindow *init(const std::string& config_path, int width, int height);

    void render(Camera& camera, const Map::Ptr& map);

    void render_map_node(Camera& camera, MapNode::Ptr &node);

    void cleanup();

    // state setters
    bool set_shader(const std::string &name);
private:
    Mesh::Ptr origin_mesh;
    std::string current_shader_name{};
    GLuint current_shader_program{};
    GLint vp_uniform{};
    GLint tex_uniform{};
    GLFWwindow* window{nullptr};
    std::unordered_map<std::string, GLuint> loaded_shaders;
    std::unordered_map<std::string, GLuint> loaded_textures;

    void
    load_shader(const std::string &name, const std::string &vertex_shader_path, const std::string &fragment_shader_path);

    void load_texture(const std::string &name, const std::string &texture_path);

    const std::string DEFAULT_SHADER_NAME{"color"};

    const std::string NAME_KEY{"name"};
    const std::string SHADERS_KEY{"shaders"};
    const std::string SPRITES_KEY{"sprites"};
    const std::string TILESIZE_KEY{"tilesize"};
    const std::string TEXTURE_KEY{"texture"};
    const std::string TEXTURES_KEY{"textures"};
    const json CONFIG_SCHEMA{
            {"title", "Renderer initialization config"},
            {"type", "object"},
            {"properties", {
                {TILESIZE_KEY, {
                    {"description", "Size of tiles to render on maps"},
                    {"type", "integer"}
                }},
                {TEXTURES_KEY, {
                    {"description", "Texture files to load"},
                    {"type", "object"}
                }},
                {SHADERS_KEY, {
                    {"description", "Shader names and files"},
                    {"type", "object"}
                }}
              }},
    {"required", {TILESIZE_KEY, TEXTURES_KEY, SHADERS_KEY}}
    };
    const json SPRITE_SCHEMA{
            {"title",      "A screen sprite"},
            {"type",       "object"},
            {"properties", {{"width", {{"description", "Sprite width"}, {"type", "number"}}},
                           {"height", {{"description", "Sprite height"}, {"type", "number"}}},
                           {NAME_KEY, {{"description", "Sprite name"}, {"type", "string"}}},
                           {TEXTURE_KEY, {{"description", "Sprite texture"}, {"type", "string"}}}}},
            {"required",   {NAME_KEY, TEXTURE_KEY}}
    };
    const json TILESHEET_SCHEMA{
            {"title",      "A tile sheet"},
            {"type",       "object"},
            {"properties", {{NAME_KEY, {{"description", "Tilesheet name"}, {"type", "string"}}},
                            {TILESIZE_KEY, {{"description", "Tile size"}, {"type", "number"}}},
                            {TEXTURE_KEY, {{"description", "Tilesheet texture"}, {"type", "string"}}},
                            {SPRITES_KEY, {{"description", "Tile names"}, {"type", "array"}}}}},
            {"required",   {NAME_KEY, TILESIZE_KEY, TEXTURE_KEY, SPRITES_KEY}}
    };
};

#endif //SOCIETY_RENDERER_H
