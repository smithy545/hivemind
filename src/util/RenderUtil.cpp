//
// Created by Philip on 3/1/2020.
//

#include "RenderUtil.h"

#include <CImg.h>
#include <iostream>

#include "FileUtil.h"


using namespace cimg_library;

GLuint RenderUtil::loadShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    // vertex shader
    char *vertexShaderSource = FileUtil::readResourceFile("shaders/" + vertexShaderPath);
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Error on vertex compilation: " << infoLog << std::endl;
        return -1;
    }
    delete[] vertexShaderSource;

    // fragment shader
    char *fragmentShaderSource = FileUtil::readResourceFile("shaders/" + fragmentShaderPath);
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Error on fragment compilation: " << infoLog << std::endl;
        return -1;
    }
    delete[] fragmentShaderSource;

    // compile shader program
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Error linking program: " << infoLog << std::endl;
        return -1;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}


GLuint RenderUtil::loadTexture(const std::string &texturePath, int &width, int &height) {
    // ensure graphics magick and maybe image magick are installed for this
    CImg<unsigned char> image(("../res/img/" + texturePath).c_str());

    // padded image width (image size + padding for texture alignment)
    int xoffset = image.width() % 8;
    int yoffset = image.height() % 8;
    int w = xoffset == 0 ? image.width() : image.width() + (8 - xoffset);
    int h = yoffset == 0 ? image.height() : image.height() + (8 - yoffset);
    // set output references
    width = image.width();
    height = image.height();

    // interleave color data from  cimg format (RRR...GGG...BBB... -> RGBRGBRGB...)
    int channels = image.spectrum();
    auto *data = new unsigned char[w * h * channels * image.depth()];
    for (int y = 0; y < h; y++) {
        // load image data
        for (int x = 0; x < w; x++) {
            int index = y * w + x;
            for (int c = 0; c < channels; c++) {
                if (x < width && y < height)
                    data[channels * index + c] = image(x, y, c);
                else
                    data[channels * index + c] = 0;
            }
        }
    }

    // texture is byte aligned
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    delete[] data;

    return textureID;
}
