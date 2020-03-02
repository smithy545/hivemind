#version 430 core

layout (location = 0) in vec2 aPos;

uniform float mouseX;
uniform float mouseY;
uniform mat4 MVP;


out vec2 mousePos;

void main() {
    gl_Position = MVP * vec4(aPos, 0, 1.0);
    mousePos = vec2(mouseX/800.0, mouseY/600.0);
}
