#version 430 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 texUv;

uniform float mouseX;
uniform float mouseY;
uniform mat4 MVP;

out vec2 uv;


void main() {
    gl_Position = MVP * vec4(aPos, 0, 1.0);
    uv = vec2(texUv.x, 1 - texUv.y);
}
