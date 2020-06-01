//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_RENDERER_H
#define SOCIETY_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "Camera.h"
#include "RenderNode.h"
#include "Sprite.h"


using namespace nlohmann;

class Renderer {
public:
    typedef std::shared_ptr<Renderer> Ptr;

    Renderer();

    // lifecycle methods
    GLFWwindow *init(const std::string& configPath);

    void render(RenderNode::Ptr treeHead, const Camera::Ptr &camera);

    void cleanup();

    // resize callback
    void resize(int width, int height);

    // state getters
    int getWidth() const;

    int getHeight() const;

    // state setters
    bool setShader(const std::string &name);

private:
    const std::string NAME_KEY{"name"};
    const std::string WIDTH_KEY{"width"};
    const std::string HEIGHT_KEY{"height"};
    const std::string SHADERS_KEY{"shaders"};
    const std::string SPRITES_KEY{"sprites"};
    const std::string SPRITESHEETS_KEY{"spritesheets"};
    const std::string TILESHEETS_KEY{"tilesheets"};
    const std::string TILESIZE_KEY{"tilesize"};
    const std::string TEXTURE_KEY{"texture"};
    const std::string TEXTURES_KEY{"textures"};
    const std::string DEFAULT_SHADER_NAME{"texture"};
    const json CONFIG_SCHEMA{
        {"title", "Renderer initialization config"},
        {"type", "object"},
        {"properties", {
            {WIDTH_KEY, {
                {"description", "Initial width of rendered window"},
                {"type", "integer"}
            }},
            {HEIGHT_KEY, {
                {"description", "Initial height of rendered window"},
                {"type", "integer"}
            }},
            {SPRITESHEETS_KEY, {
                {"description", "Names of json files containing sprite information"},
                {"type", "array"},
                {"items", {"type", "string"}}
            }},
            {TILESHEETS_KEY, {
                {"description", "Names of json files containing tilesheet information"},
                {"type", "array"},
                {"items", {"type", "string"}}
            }},
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
        {"required", {WIDTH_KEY, HEIGHT_KEY, SPRITESHEETS_KEY, TILESHEETS_KEY, TILESIZE_KEY, TEXTURES_KEY, SHADERS_KEY}}
    };
    const json SPRITE_SCHEMA{
            {"title",      "A screen sprite"},
            {"type",       "object"},
            {"properties", {
                                   {WIDTH_KEY, {{"description", "Sprite width"}, {"type", "number"}}},
                                   {HEIGHT_KEY, {{"description", "Sprite height"}, {"type", "number"}}},
                                   {NAME_KEY, {{"description", "Sprite name"}, {"type", "string"}}},
                                   {TEXTURE_KEY, {{"description", "Sprite texture"}, {"type", "string"}}}
                           }},
            {"required",   {NAME_KEY, TEXTURE_KEY}}
    };
    const json TILESHEET_SCHEMA{
            {"title",      "A tile sheet"},
            {"type",       "object"},
            {"properties", {
                                   {NAME_KEY, {{"description", "Tilesheet name"}, {"type", "string"}}},
                                   {TILESIZE_KEY, {{"description", "Tile size"}, {"type", "number"}}},
                                   {TEXTURE_KEY, {{"description", "Tilesheet texture"}, {"type", "string"}}},
                                   {SPRITES_KEY, {{"description", "Tile names"}, {"type", "array"}}}
                           }},
            {"required",   {NAME_KEY, TILESIZE_KEY, TEXTURE_KEY, SPRITES_KEY}}
    };

    int width{};
    int height{};
    GLuint currentShaderProgram{};
    GLint mvpUniform{};
    GLint texUniform{};
    GLFWwindow *window;
    std::unordered_map<std::string, GLuint> loadedShaders;
    std::unordered_map<std::string, Sprite::Ptr> loadedSprites;
    std::unordered_map<std::string, GLuint> loadedTextures;

    void
    loadShader(const std::string &name, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void loadTexture(const std::string &name, const std::string &texturePath);

    void loadSprite(const std::string &path);

    void loadTileSheet(const std::string &path);

    std::string generateBezierSprite(const std::vector<glm::vec2> &hull, double stepSize);
};

#endif //SOCIETY_RENDERER_H
