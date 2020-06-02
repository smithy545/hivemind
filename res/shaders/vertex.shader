#version 430 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 texUv;
layout (location = 2) in vec4 inColor;

uniform mat4 MVP;

out vec2 uv;
out vec4 color;

void main() {
    gl_Position = MVP * vec4(inPos, 1);
    uv = vec2(texUv.x, texUv.y);
    color = inColor;
}
