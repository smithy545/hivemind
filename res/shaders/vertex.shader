#version 430 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;

uniform mat4 VP;

out vec4 color;

void main() {
    gl_Position = VP * vec4(inPos, 1);
    color = inColor;
}
