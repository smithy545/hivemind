//
// Created by Philip on 3/1/2020.
//

#ifndef SOCIETY_RENDERUTIL_H
#define SOCIETY_RENDERUTIL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>


class RenderUtil {
public:
    static GLuint load_shader_program(const std::string &vertex_shader_path, const std::string &fragment_shader_path);

    static GLuint load_texture(const std::string &texture_path, int &width, int &height);
};


#endif //SOCIETY_RENDERUTIL_H
